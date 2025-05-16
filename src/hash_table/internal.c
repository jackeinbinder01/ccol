/*
 * ccol/src/hash_table/internal.c
 *
 * Hash table internal function implementations.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ccol/ccol_hash.h"
#include "ccol/ccol_constants.h"
#include "ccol/ccol_status.h"

#include "policies/simple.h"
#include "policies/robust.h"
#include "policies/secure.h"

void ccol__auto_resize(ccol_hash_table_t *hash_table);

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
) {
    if (!hash_func || !hash_table_out || num_buckets < 1 || key_size < 1) return CCOL_STATUS_INVALID_ARG;
    if (!comparator.func) return CCOL_STATUS_COMPARATOR_FUNC;

    *hash_table_out = NULL;

    ccol_hash_table_t *hash_table = calloc(1, sizeof(ccol_hash_table_t));
    if (!hash_table) return CCOL_STATUS_ALLOC;

    hash_t hasher = ccol_hash_create(hash_func, hash_ctx, policy);

    ccol_status_t status = ccol_hash_table_init(
        hash_table,
        hasher,
        copier,
        freer,
        printer,
        comparator
    );
    if (status != CCOL_STATUS_OK) {
        free(hash_table);
        return status;
    }

    hash_table->buckets = calloc(num_buckets, sizeof(dll_t *));
    if (!hash_table->buckets) {
        free(hash_table);
        return CCOL_STATUS_ALLOC;
    }

    hash_table->num_buckets = num_buckets;
    hash_table->key_size = key_size;

    *hash_table_out = hash_table;

    return CCOL_STATUS_OK;
}

ccol_status_t ccol__hash_table_get_entry(const ccol_hash_table_t *hash_table, const void *key, hash_entry_t **entry_out) {
    CCOL_CHECK_INIT(hash_table);

    ccol_dll_node_t *node = NULL;
    ccol_status_t status = ccol_hash_table_get_node(hash_table, key, &node);
    if (status != CCOL_STATUS_OK) return status;
    *entry_out = (hash_entry_t *)node->data;

    return CCOL_STATUS_OK;
}

void ccol__hash_table_unini(ccol_hash_table_t *hash_table) {
    if (!hash_table || !hash_table->is_initialized) return;

    hash_table->buckets = NULL;

    hash_table->num_buckets = 0;
    hash_table->size = 0;
    hash_table->key_size = 0;

    hash_table->hasher = (hash_t){0};
    hash_table->copier = (copy_t){0};
    hash_table->freer = (free_t){0};
    hash_table->printer = (print_t){0};
    hash_table->comparator = (comparator_t){0};

    hash_table->is_initialized = false;
}
