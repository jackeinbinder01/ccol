/*
 * ccol/hash_table.c
 *
 * Hash table implementation
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dll.h"
#include "hash.h"
#include "hash_table_internal.h"
#include "hash_table_iterator.h"
#include "comparator.h"
#include "ccol_status.h"
#include "ccol_constants.h"

// Create / Initialize
ccol_status_t hash_table_init(hash_table_t *hash_table) {
    if (!hash_table) return CCOL_STATUS_INVALID_ARG;

    hash_table->buckets = NULL;
    hash_table->num_buckets = 0;
    hash_table->size = 0;
    hash_table->key_size = 0;
    hash_table->policy = 0;
    hash_table->hash_func = NULL;
    hash_table->cmp = NULL;
    hash_table->is_initialized = true;

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_create(
    size_t num_buckets,
    size_t key_size,
    hash_policy_t policy,
    comparator_t cmp,
    hash_table_t **hash_table_out
) {
    if (num_buckets < 1 || key_size < 1
        || policy < HASH_SIMPLE || policy > HASH_SECURE
        || !cmp || !hash_table_out)
        return CCOL_STATUS_INVALID_ARG;

    hash_func_t hash_func = resolve_hash_func(key_size, policy);
    if (!hash_func) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = hash_table_create_internal(num_buckets, key_size, policy, hash_func, cmp, hash_table_out);
    if (status != CCOL_STATUS_OK) {
        return status;
    }

    return CCOL_STATUS_OK
}

ccol_status_t hash_table_create_custom(
    size_t num_buckets,
    size_t key_size,
    hash_func_t hash_func,
    comparator_t cmp,
    hash_table_t **hash_table_out
) {
    if (num_buckets < 1 || key_size < 1 || !hash_func || !cmp || !hash_table_out) return CCOL_STATUS_INVALID_ARG;

    hash_policy_t policy = HASH_CUSTOM;
    ccol_status_t status = hash_table_create_internal(num_buckets, key_size, policy, hash_func, cmp, hash_table_out);
    if (status != CCOL_STATUS_OK) {
        return status;
    }

    return CCOL_STATUS_OK
}

// Insertion
ccol_status_t hash_table_insert(hash_table_t *hash_table, void *key, void *data) {
    CCOL_CHECK_INIT(hash_table);

    size_t hash_key = hash_table->hash_func(key) % hash_table->num_buckets;
    if (!(hash_table->buckets[hash_key])) {
        ccol_status_t status = dll_create(&hash_table->buckets[hash_key]);
        if (status != CCOL_STATUS_OK) return status;
    }

    ccol_status_t status = dll_push(hash_table->buckets[hash_key], data);
    if (status != CCOL_STATUS_OK) return status;

    hash_table->size++;
    return CCOL_STATUS_OK;
}

// Removal
ccol_status_t hash_table_remove(hash_table_t *hash_table, void *key) {
    CCOL_CHECK_INIT(hash_table);

    size_t hash_key = hash_table->hash_func(key) % hash_table->num_buckets;
    dll_t *bucket = hash_table->buckets[hash_key];
    if (!bucket) return CCOL_STATUS_NOT_FOUND;
    ccol_status_t status = dll_remove(bucket, key, hash_table->cmp);
    if (status != CCOL_STATUS_OK) return status;

    hash_table->size--;
    return CCOL_STATUS_OK;
}

// Access
ccol_status_t hash_table_get_node(const hash_table_t *hash_table, void *key, dll_node_t **node_out) {
    CCOL_CHECK_INIT(hash_table);

    size_t hash_key = hash_table->hash_func(key) % hash_table->num_buckets;
    dll_t *bucket = hash_table->buckets[hash_key];
    if (!bucket) return CCOL_STATUS_NOT_FOUND;
    dll_node_t *node = dll_search(bucket, key, hash_table->cmp, data_out);
    if (!node) return CCOL_STATUS_NOT_FOUND;
    *node_out = node;

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_get(const hash_table_t *hash_table, void *key, void **data_out) {
    CCOL_CHECK_INIT(hash_table);

    dll_node_t *node = NULL;
    ccol_status_t status = hash_table_get_node(hash_table, key, &node);
    if (status != CCOL_STATUS_OK) return status;
    *data_out = node->data;

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_get_all_keys(const hash_table_t *hash_table, void ***keys_out, size_t *key_count);

// Attributes
bool hash_table_is_empty(const hash_table_t *hash_table) {
    return (!hash_table || !hash_table->is_initialized || hash_table->size == 0);
}

size_t hash_table_size(const hash_table_t *hash_table) {
    if (!hash_table || !hash_table->is_initialized) return 0;
    return hash_table->size;
}

size_t hash_table_num_buckets(const hash_table_t *hash_table) {
    if (!hash_table || !hash_table->is_initialized) return 0;
    return hash_table->num_buckets;
}

bool hash_table_contains(const hash_table_t *hash_table, const void *key);
bool hash_table_contains_key(const hash_table_t *hash_table, void *key);
double hash_table_load_factor(const hash_table_t *hash_table);

// Utilities
ccol_status_t hash_table_swap(hash_table_t *hash_table, void *key1, void *key2);
ccol_status_t hash_table_resize(hash_table_t *hash_table, int new_num_buckets);

// Copy / Clone
ccol_status_t hash_table_clone(const hash_table_t *src, hash_table_t **hash_table_out, void *(*copy_data)(const void *));
ccol_status_t hash_table_deep_clone(const hash_table_t *src, hash_table_t **hash_table_out);
ccol_status_t hash_table_copy(hash_table_t *dest, hash_table_t *src, void (*free_data)(void *), void *(*copy_data)(const void *));
ccol_status_t hash_table_deep_copy(hash_table_t *dest, hash_table_t *src, void (*free_data)(void *));

// Cleanup
ccol_status_t hash_table_clear_bucket(hash_table_t *hash_table, int bucket_index, void (*free_data)(void *));
void hash_table_clear(hash_table_t *hash_table, void (*free_data)(void *));
void hash_table_destroy(hash_table_t *hash_table, void (*free_data)(void *));
void hash_table_free(hash_table_t *hash_table, void (*free_data)(void *));

// Print / Debug
ccol_status_t hash_table_print(hash_table_t *hash_table, void (*print_data)(const void *));
