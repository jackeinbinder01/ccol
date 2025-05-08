/*
 * ccol/hash_table.h
 *
 * Hash table
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include <stdbool.h>
#include "dll.h"
#include "hash.h"
#include "hash_table_internal.h"
#include "hash_table_iterator.h"
#include "comparator.h"

typedef struct hash_table_t {
    dll_t **buckets;
    size_t num_buckets;
    size_t size;
    size_t key_size;

    hash_policy_t policy;
    hash_func_t hash_func;

    copy_func_t copy_func;
    free_func_t free_func;
    print_func_t print_func;

    comparator_t cmp;
    void *ctx;

    bool is_initialized;
} hash_table_t;

// Create / Initialize
ccol_status_t hash_table_init(hash_table_t *hash_table);
ccol_status_t hash_table_create(size_t num_buckets, size_t key_size, hash_policy_t policy, comparator_t cmp, hash_table_t **hash_table_out);
ccol_status_t hash_table_create_custom(size_t num_buckets, size_t key_size, hash_func_t hash_func, comparator_t cmp, hash_table_t **hash_table_out);

// Insertion
ccol_status_t hash_table_insert(hash_table_t *hash_table, void *key, void *data, void *ctx);

// Removal
ccol_status_t hash_table_remove(hash_table_t *hash_table, void *key, void *ctx);

// Access
ccol_status_t hash_table_get(const hash_table_t *hash_table, const void *key, void **data_out, void *ctx);
ccol_status_t hash_table_get_node(const hash_table_t *hash_table, const void *key, dll_node_t **node_out, void *ctx);
ccol_status_t hash_table_get_entry(const hash_table_t *hash_table, const void *key, hash_entry_t **entry_out, void *ctx);
ccol_status_t hash_table_get_all_keys(const hash_table_t *hash_table, void ***keys_out, size_t *key_count);

// Attributes
bool hash_table_is_empty(const hash_table_t *hash_table);
size_t hash_table_size(const hash_table_t *hash_table);
size_t hash_table_num_buckets(const hash_table_t *hash_table);

bool hash_table_contains(const hash_table_t *hash_table, const void *key, void *ctx); // default wrapper over contains key
bool hash_table_contains_key(const hash_table_t *hash_table, const void *key);
bool hash_table_contains_value(const hash_table_t *hash_table, void *value, void *ctx);
double hash_table_load_factor(const hash_table_t *hash_table);

// Utilities
ccol_status_t hash_table_swap(hash_table_t *hash_table, void *key1, void *key2, void *ctx);
ccol_status_t hash_table_resize(hash_table_t *hash_table, int new_num_buckets);

// Copy / Clone
ccol_status_t hash_table_clone(const hash_table_t *src, hash_table_t **hash_table_out, copy_func_t copy_data, void *ctx);
ccol_status_t hash_table_deep_clone(const hash_table_t *src, hash_table_t **hash_table_out, void *ctx);
ccol_status_t hash_table_copy(hash_table_t *dest, hash_table_t *src, free_func_t free_data, copy_func_t copy_data, void *ctx);
ccol_status_t hash_table_deep_copy(hash_table_t *dest, hash_table_t *src, free_func_t free_data, void *ctx);

// Cleanup
ccol_status_t hash_table_clear_bucket(hash_table_t *hash_table, int bucket_index, free_func_t free_data, void *ctx);
void hash_table_clear(hash_table_t *hash_table, free_func_t free_data, void *ctx);
void hash_table_destroy(hash_table_t *hash_table, free_func_t free_data, void *ctx);
void hash_table_free(hash_table_t **hash_table_ptr, free_func_t free_data, void *ctx);

// Print / Debug
ccol_status_t hash_table_print(hash_table_t *hash_table, print_func_t print_data, void *ctx);

#endif // HASH_TABLE_H
