/*
 * ccol/ccol_hash_table.h
 *
 * Hash table API.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_HASH_TABLE_H
#define CCOL_HASH_TABLE_H

#include <stddef.h>
#include <stdbool.h>

#include "ccol_dll.h"
#include "ccol_hash.h"
#include "ccol_hash_table_iterator.h"
#include "ccol_comparator.h"

typedef struct ccol_hash_table {
    ccol_dll_t **buckets;
    size_t num_buckets;
    size_t size;
    size_t key_size;

	ccol_hash_t hasher;

    ccol_copy_t copier;
    ccol_free_t freer;
    ccol_print_t printer;
    ccol_comparator_t comparator;

    bool is_initialized;
} ccol_hash_table_t;

// Create / Initialize
ccol_status_t ccol_hash_table_init(
    ccol_hash_table_t *hash_table,
    ccol_hash_t hasher,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

ccol_status_t ccol_hash_table_create(
    ccol_hash_table_t **hash_table_out,
    size_t num_buckets,
    size_t key_size,
    ccol_hash_policy_t policy,
    ccol_hash_t hasher,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

// Insertion
ccol_status_t ccol_hash_table_insert(ccol_hash_table_t *hash_table, void *key, void *data);

// Removal
ccol_status_t ccol_hash_table_remove(ccol_hash_table_t *hash_table, void *key);

// Access
ccol_status_t ccol_hash_table_get_node(const ccol_hash_table_t *hash_table, const void *key, ccol_dll_node_t **node_out);
ccol_status_t ccol_hash_table_get(const ccol_hash_table_t *hash_table, const void *key, void **data_out);
ccol_status_t ccol_hash_table_get_all_keys(const ccol_hash_table_t *hash_table, void ***keys_out, size_t *key_count);

// Attributes
bool ccol_hash_table_is_empty(const ccol_hash_table_t *hash_table);
size_t ccol_hash_table_size(const ccol_hash_table_t *hash_table);
size_t ccol_hash_table_num_buckets(const ccol_hash_table_t *hash_table);

bool ccol_hash_table_contains_key(const ccol_hash_table_t *hash_table, const void *key);
bool ccol_hash_table_contains(const ccol_hash_table_t *hash_table, const void *key); // default wrapper over contains key
bool ccol_hash_table_contains_value(const ccol_hash_table_t *hash_table, void *value, void *ctx);
double ccol_hash_table_load_factor(const ccol_hash_table_t *hash_table);

// Utilities
ccol_status_t ccol_hash_table_swap(ccol_hash_table_t *hash_table, void *key1, void *key2);
ccol_status_t ccol_hash_table_resize(ccol_hash_table_t *hash_table, int new_num_buckets);

// Copy / Clone
ccol_status_t ccol_hash_table_clone(const ccol_hash_table_t *src, ccol_hash_table_t **hash_table_out);
ccol_status_t ccol_hash_table_deep_clone(const ccol_hash_table_t *src, ccol_hash_table_t **hash_table_out);
ccol_status_t ccol_hash_table_shallow_clone(const ccol_hash_table_t *src, ccol_hash_table_t **hash_table_out);

ccol_status_t ccol_hash_table_copy(ccol_hash_table_t *dest, const ccol_hash_table_t *src);
ccol_status_t ccol_hash_table_deep_copy(ccol_hash_table_t *dest, const ccol_hash_table_t *src);
ccol_status_t ccol_hash_table_shallow_copy(ccol_hash_table_t *dest, const ccol_hash_table_t *src);

// Cleanup
ccol_status_t ccol_hash_table_clear_bucket(ccol_hash_table_t *hash_table, int bucket_index);
ccol_status_t ccol_hash_table_clear(ccol_hash_table_t *hash_table);
ccol_status_t ccol_hash_table_destroy(ccol_hash_table_t *hash_table);
ccol_status_t ccol_hash_table_free(ccol_hash_table_t **hash_table_ptr);

// Print / Debug
ccol_status_t ccol_hash_table_print(ccol_hash_table_t *hash_table);

#endif  // CCOL_HASH_TABLE_H
