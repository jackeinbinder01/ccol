/*
 * ccol/hash_table_internal.h
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef HASH_TABLE_INTERNAL_H
#define HASH_TABLE_INTERNAL_H

#include <stddef.h>
#include "hash.h"
#include "hash_table_iterator.h"
#include "comparator.h"

typedef struct {
	void *key;
    void *value;
} hash_entry_t;

ccol_status_t hash_table_create_internal(
    int num_buckets,
    size_t key_size,
    hash_policy_t policy,
    hash_func_t hash_func,
    copy_func_t copy_func,
    free_func_t free_func,
    print_func_t print_func,
    comparator_t cmp,
    void *ctx,
    hash_table_t **hash_table_out
);

hash_func_t resolve_hash_func(size_t key_size, hash_policy_t policy);
void hash_table_uninit(hash_table_t *hash_table);

#endif // HASH_TABLE_INTERNAL_H