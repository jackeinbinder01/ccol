/*
 * ccol/hash_table_internal.c
 *
 * Hash table internal functions
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "hash_table_internal.h"
#include "hash.h"
#include "hash_simple.h"
#include "hash_robust.h"
#include "hash_secure.h"
#include "hash_table.h"
#include "ccol_constants.h"
#include "ccol_status.h"

void auto_resize(hash_table_t *hash_table);

ccol_status_t hash_table_create_internal(
    int num_buckets,
    size_t key_size,
    hash_policy_t policy,
    hash_func_t hash_func,
    void *hash_ctx,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator,
    hash_table_t **hash_table_out
) {
    if (!hash_func || !hash_table_out || num_buckets < 1 || key_size < 1) return CCOL_STATUS_INVALID_ARG;
    if (!comparator.func) return CCOL_STATUS_COMPARATOR_FUNC;

    hash_table_t *hash_table = calloc(1, sizeof(hash_table_t));
    if (!hash_table) return CCOL_STATUS_ALLOC;

    hash_t hasher = hash_create(hash_func, hash_ctx, policy);

    ccol_status_t status = hash_table_init(
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

void hash_table_uninit(hash_table_t *hash_table) {
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
