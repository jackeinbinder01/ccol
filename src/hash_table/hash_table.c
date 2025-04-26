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
#include <stdio.h>

#include "dll.h"
#include "hash.h"
#include "hash_table.h"
#include "hash_table_internal.h"
#include "hash_table_iterator.h"
#include "comparator.h"
#include "ccol_status.h"
#include "ccol_constants.h"
#include "ccol_macros.h"

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
    if (num_buckets < 1 ||
      	key_size < 1 ||
    	policy < HASH_SIMPLE || policy > HASH_SECURE ||
    	!cmp ||
     	!hash_table_out)
	{
    	return CCOL_STATUS_INVALID_ARG;
	}

    hash_func_t hash_func = resolve_hash_func(key_size, policy);
    if (!hash_func) return CCOL_STATUS_INVALID_ARG;

    return hash_table_create_internal(num_buckets, key_size, policy, hash_func, cmp, hash_table_out);
}

ccol_status_t hash_table_create_custom(
    size_t num_buckets,
    size_t key_size,
    hash_func_t hash_func,
    comparator_t cmp,
    hash_table_t **hash_table_out
) {
    if (num_buckets < 1 ||
    	key_size < 1 ||
    	!hash_func ||
    	!cmp ||
      	!hash_table_out)
    {
    	return CCOL_STATUS_INVALID_ARG;
    }

    hash_policy_t policy = HASH_CUSTOM;

    return hash_table_create_internal(num_buckets, key_size, policy, hash_func, cmp, hash_table_out);
}

// Insertion
ccol_status_t hash_table_insert(hash_table_t *hash_table, void *key, void *data, void *ctx) {
    CCOL_CHECK_INIT(hash_table);
    if (!key) return CCOL_STATUS_INVALID_ARG;

    size_t hash_key = hash_table->hash_func(key) % hash_table->num_buckets;
    ccol_status_t status;
    if (!(hash_table->buckets[hash_key])) {
        status = dll_create(&hash_table->buckets[hash_key]);
        if (status != CCOL_STATUS_OK) return status;
    }

    dll_node_t *duplicate = dll_search(hash_table->buckets[hash_key], key, hash_table->cmp, ctx);
    if (duplicate) return CCOL_STATUS_ALREADY_EXISTS;

    hash_entry_t *entry = malloc(sizeof(hash_entry_t));
    if (!entry) return CCOL_STATUS_ALLOC;
    entry->key = key;
    entry->value = data;

    status = dll_push(hash_table->buckets[hash_key], entry);
    if (status != CCOL_STATUS_OK) {
        free(entry);
        return status;
    }

    hash_table->size++;
    return CCOL_STATUS_OK;
}

// Removal
ccol_status_t hash_table_remove(hash_table_t *hash_table, void *key, free_func_t free_data, void *ctx) {
    CCOL_CHECK_INIT(hash_table);

    size_t hash_key = hash_table->hash_func(key) % hash_table->num_buckets;
    dll_t *bucket = hash_table->buckets[hash_key];
    if (!bucket) return CCOL_STATUS_NOT_FOUND;

    ccol_status_t status = dll_remove(bucket, key, hash_table->cmp, free_data, ctx);
    if (status != CCOL_STATUS_OK) return status;

    hash_table->size--;
    return CCOL_STATUS_OK;
}

// Access
ccol_status_t hash_table_get_node(const hash_table_t *hash_table, void *key, dll_node_t **node_out, void *ctx) {
    CCOL_CHECK_INIT(hash_table);

    size_t hash_key = hash_table->hash_func(key) % hash_table->num_buckets;
    dll_t *bucket = hash_table->buckets[hash_key];
    if (!bucket) return CCOL_STATUS_NOT_FOUND;

    dll_node_t *node = dll_search(bucket, key, hash_table->cmp, ctx);
    if (!node) return CCOL_STATUS_NOT_FOUND;

    *node_out = node;

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_get(const hash_table_t *hash_table, void *key, void **data_out, void *ctx) {
    CCOL_CHECK_INIT(hash_table);

    dll_node_t *node = NULL;
    ccol_status_t status = hash_table_get_node(hash_table, key, &node, ctx);
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

bool hash_table_contains(const hash_table_t *hash_table, const void *key, void *ctx) {
    return hash_table_contains_key(hash_table, key, ctx);
}

bool hash_table_contains_key(const hash_table_t *hash_table, const void *key, void *ctx) {
    if (!hash_table || !hash_table->is_initialized) return 0;

    size_t hash_key = hash_table->hash_func(key) % hash_table->num_buckets;
    dll_t *bucket = hash_table->buckets[hash_key];
    if (!bucket) return false;

    return dll_contains(bucket, key, hash_table->cmp, ctx);
}

bool hash_table_contains_value(const hash_table_t *hash_table, void *key, void *value, void *ctx) {
    if (!hash_table || !hash_table->is_initialized) return 0;

    size_t hash_key = hash_table->hash_func(key) % hash_table->num_buckets;
    dll_t *bucket = hash_table->buckets[hash_key];
    if (!bucket) return false;

    return dll_contains(bucket, value, hash_table->cmp);
}

double hash_table_load_factor(const hash_table_t *hash_table);

// Utilities
int cmp_hash_entry_key(const void *a, const void *b) {
    const hash_entry_t *entry = a;


}

ccol_status_t hash_table_swap(hash_table_t *hash_table, void *key1, void *key2, void *ctx);
ccol_status_t hash_table_resize(hash_table_t *hash_table, int new_num_buckets);

// Copy / Clone
ccol_status_t hash_table_clone(const hash_table_t *src, hash_table_t **hash_table_out, copy_func_t copy_data, void *ctx) {
    CCOL_CHECK_INIT(src);
    if (!hash_table_out || !copy_data) return CCOL_STATUS_INVALID_ARG;
    
    ccol_status_t status;
    if (src->policy == HASH_CUSTOM) {
        status = hash_table_create_custom(src->num_buckets, src->key_size, src->hash_func, src->cmp, hash_table_out);
    } else {
        status = hash_table_create(src->num_buckets, src->key_size, src->policy, src->cmp, hash_table_out);
    }

    if (status != CCOL_STATUS_OK) return status;

    if (!src->buckets) return CCOL_STATUS_OK;

    for (size_t i = 0; i < src->num_buckets; i++) {
        dll_t *src_bucket = src->buckets[i];
        if (!src_bucket) continue;

        dll_t* dest_bucket = NULL;
        status = dll_create(&dest_bucket);
        if (status != CCOL_STATUS_OK) {
            hash_table_destroy(hash_table_out);
            return status;
        }

        status = dll_clone(src_bucket, &dest_bucket, copy_data, ctx);
        if (status != CCOL_STATUS_OK) {
            dll_destroy(&dest_bucket);
            hash_table_destroy(hash_table_out);
            return status;

        }

        (*hash_table_out)->buckets[i] = dest_bucket;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_deep_clone(const hash_table_t *src, hash_table_t **hash_table_out, void *ctx) {
    CCOL_CHECK_INIT(src);
    if (!hash_table_out) return CCOL_STATUS_INVALID_ARG;

    return hash_table_clone(src, hash_table_out, COPY_DEFAULT, ctx);
}

ccol_status_t hash_table_copy(hash_table_t *dest, hash_table_t *src, free_func_t free_data, copy_func_t copy_data, void *ctx) {
    CCOL_CHECK_INIT(dest);
    CCOL_CHECK_INIT(src);
    
    if (!copy_data) return CCOL_STATUS_INVALID_ARG;

    dll_clear(dest, free_data, ctx);

}
ccol_status_t hash_table_deep_copy(hash_table_t *dest, hash_table_t *src, free_func_t free_data, void *ctx);

// Cleanup
ccol_status_t hash_table_clear_bucket(hash_table_t *hash_table, int bucket_index, free_func_t free_data, void *ctx) {
	CCOL_CHECK_INIT(hash_table);
    if (bucket_index < 0 || bucket_index > ((int)hash_table->num_buckets - 1)) return CCOL_STATUS_OUT_OF_BOUNDS;
    if (hash_table->size == 0) return CCOL_STATUS_SUCCESS;

    dll_t *bucket = hash_table->buckets[bucket_index];
    if (!bucket) return CCOL_STATUS_NOT_FOUND;

    hash_table->size -= dll_size(bucket);
    dll_clear(bucket, free_data, ctx);

    return CCOL_STATUS_OK;
}

void hash_table_clear(hash_table_t *hash_table, free_func_t free_data, void *ctx) {
	if (!hash_table || !hash_table->is_initialized) return;
    if (hash_table->size == 0) return;

    for (size_t i = 0; i < hash_table->num_buckets; i++) {
    	dll_t *bucket = hash_table->buckets[i];
        if (!bucket) continue;
    	dll_clear(bucket, free_data, ctx);
    }

    hash_table->size = 0;
}

void hash_table_destroy(hash_table_t *hash_table, free_func_t free_data, void *ctx) {
	if (!hash_table || !hash_table->is_initialized) return;

    for (size_t i = 0; i < hash_table->num_buckets; i++) {
    	dll_t *bucket = hash_table->buckets[i];
        if (!bucket) continue;
    	dll_destroy(bucket, free_data, ctx);
        free(bucket);
    }

    hash_table_uninit(hash_table);
}

void hash_table_free(hash_table_t **hash_table_ptr, free_func_t free_data, void *ctx) {
	if (!hash_table_ptr || !*hash_table_ptr || !(*hash_table_ptr)->is_initialized) return;

    hash_table_destroy(*hash_table_ptr, free_data, ctx);
    free(*hash_table_ptr);
    *hash_table_ptr = NULL;
}

// Print / Debug
ccol_status_t hash_table_print(hash_table_t *hash_table, print_func_t print_data, void *ctx) {
	CCOL_CHECK_INIT(hash_table);
    if (!print_data) return CCOL_STATUS_INVALID_ARG;
    if (hash_table->size == 0) {
    	printf("[]\n");
        return CCOL_STATUS_OK;
    }

    ccol_status_t status = CCOL_STATUS_OK;
    for (size_t i = 0; i < hash_table->num_buckets; i++) {
    	dll_t *bucket = hash_table->buckets[i];
        if (!bucket) continue;

        printf("Bucket[%zu]: ", i);
        status = dll_print(bucket, print_data, ctx);
        if (status != CCOL_STATUS_OK) return status;
    }

    return CCOL_STATUS_OK;
}
