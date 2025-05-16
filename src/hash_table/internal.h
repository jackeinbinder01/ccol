/*
 * ccol/src/hash_table/internal.h
 *
 * Hash table internal functions.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_HASH_TABLE_INTERNAL_H
#define CCOL_HASH_TABLE_INTERNAL_H

#include <stddef.h>

#include "ccol/ccol_hash.h"
#include "ccol/ccol_hash_table.h"
#include "ccol/ccol_status.h"

ccol_status_t ccol__hash_table_create_internal(
    ccol_hash_table_t **hash_table_out,
    int num_buckets,
    size_t key_size,
    ccol_hash_policy_t policy,
    ccol_hash_func_t hash_func,
    void *hash_ctx,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

ccol_status_t ccol__resolve_hash_func(size_t key_size, ccol_hash_policy_t policy, ccol_hash_func_t *hash_func_out);
ccol_status_t ccol__hash_table_get_entry(
    const ccol_hash_table_t *hash_table,
    const void *key,
    ccol_hash_entry_t **entry_out
);

void ccol__hash_table_uninit(ccol_hash_table_t *hash_table);

#endif  // CCOL_HASH_TABLE_INTERNAL_H