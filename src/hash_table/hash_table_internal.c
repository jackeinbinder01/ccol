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
#include "hash.h"
#include "hash_table.h"
#include "ccol_constants.h"
#include "ccol_status.h"

void auto_resize(hash_table_t *hash_table);

ccol_status_t resolve_hash_func(size_t key_size, hash_policy_t policy, hash_func_t *hash_func_out) {
    if (policy == HASH_CUSTOM) return CCOL_STATUS_OK;
    if (policy < HASH_SIMPLE || policy > HASH_SECURE) return CCOL_STATUS_HASH_POLICY;

    if (key_size == HASH_KEY_STRING) {
        switch(policy) {
            case HASH_SIMPLE: *hash_func_out = hash_simple_str; return CCOL_STATUS_OK;
            case HASH_ROBUST: *hash_func_out = hash_robust_str; return CCOL_STATUS_OK;
            case HASH_SECURE: *hash_func_out = hash_secure_str; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    if (key_size == sizeof(int8_t) || key_size == sizeof(uint8_t)) {
        switch(policy) {
            case HASH_SIMPLE: *hash_func_out = hash_simple_uint8; return CCOL_STATUS_OK;
            case HASH_ROBUST: *hash_func_out = hash_robust_uint8; return CCOL_STATUS_OK;
            case HASH_SECURE: *hash_func_out = hash_secure_uint8; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    if (key_size == sizeof(int16_t) || key_size == sizeof(uint16_t)) {
        switch(policy) {
            case HASH_SIMPLE: *hash_func_out = hash_simple_uint16; return CCOL_STATUS_OK;
            case HASH_ROBUST: *hash_func_out = hash_robust_uint16; return CCOL_STATUS_OK;
            case HASH_SECURE: *hash_func_out = hash_secure_uint16; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    if (key_size == sizeof(int32_t) || key_size == sizeof(uint32_t)) {
        switch(policy) {
            case HASH_SIMPLE: *hash_func_out = hash_simple_uint32; return CCOL_STATUS_OK;
            case HASH_ROBUST: *hash_func_out = hash_robust_uint32; return CCOL_STATUS_OK;
            case HASH_SECURE: *hash_func_out = hash_secure_uint32; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    if (key_size == sizeof(int64_t) || key_size == sizeof(uint64_t)) {
        switch(policy) {
            case HASH_SIMPLE: *hash_func_out = hash_simple_uint64; return CCOL_STATUS_OK;
            case HASH_ROBUST: *hash_func_out = hash_robust_uint64; return CCOL_STATUS_OK;
            case HASH_SECURE: *hash_func_out = hash_secure_uint64; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    if (key_size == sizeof(void *)) {
        switch(policy) {
            case HASH_SIMPLE: *hash_func_out = hash_simple_ptr; return CCOL_STATUS_OK;
            case HASH_ROBUST: *hash_func_out = hash_robust_ptr; return CCOL_STATUS_OK;
            case HASH_SECURE: *hash_func_out = hash_secure_ptr; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    *hash_func_out = NULL;
    return CCOL_STATUS_KEY_SIZE;
}

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
        policy,
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
    hash_table->policy = 0;

    hash_table->hasher = (hash_t){0};
    hash_table->copier = (copy_t){0};
    hash_table->freer = (free_t){0};
    hash_table->printer = (print_t){0};
    hash_table->comparator = (comparator_t){0};

    hash_table->is_initialized = false;
}
