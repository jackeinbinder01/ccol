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

ccol_status_t hash_table_create_internal(
    int num_buckets,
    size_t key_size,
    hash_policy_t policy,
    hash_func_t hash_func,
    comparator_t cmp,
    hash_table_t **hash_table_out
);

#endif // HASH_TABLE_INTERNAL_H