/*
 * ccol/hash_table.c
 *
 * Hash table implementation
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdbool.h>
#include "dll.h"
#include "hash.h"
#include "hash_table_iterator.h"
#include "comparator.h"

// Create / Initialize
ccol_status_t hash_table_init(hash_table_t *hash_table);
ccol_status_t hash_table_create(int num_buckets, size_t key_size, hash_policy_t hash_policy, comparator_t cmp, hash_table_t **hash_table_out);
ccol_status_t hash_table_create_custom(int num_buckets, size_t key_size, hash_func_t hash_func, comparator_t cmp, hash_table_t **hash_table_out);

// Insertion
ccol_status_t hash_table_insert(hash_table_t *hash_table, void *key, void *data);

// Removal
ccol_status_t hash_table_remove(hash_table_t *hash_table, void *key);

// Access
ccol_status_t hash_table_get(const hash_table_t *hash_table, void *key, void **data_out);
ccol_status_t hash_table_get_node(const hash_table_t *hash_table, void *key, dll_node_t **node_out);
ccol_status_t hash_table_get_all_keys(const hash_table_t *hash_table, void ***keys_out, size_t *key_count);

// Attributes
bool hash_table_is_empty(const hash_table_t *hash_table);
size_t hash_table_size(const hash_table_t *hash_table);
int hash_table_num_buckets(const hash_table_t *hash_table);

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
