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

#include "hash_table_internal.h"
#include "hash.h"
#include "hash_simple.h"
#include "hash_robust.h"
#include "hash_secure.h"
#include "hash.h"
#include "hash_table.h"
#include "ccol_constants.h"
#include "ccol_status.h"

#include <stdio.h>

void auto_resize(hash_table_t *hash_table);

hash_func_t resolve_hash_func(size_t key_size, hash_policy_t policy) {
    if (key_size == HASH_KEY_STRING) {
        switch(policy) {
                case HASH_SIMPLE: return hash_simple_str;
                case HASH_ROBUST: return hash_robust_str;
                case HASH_SECURE: return hash_secure_str;
                default:
                    fprintf(stderr, "resolve_hash_func: invalid hash policy: %d\n", policy);
                    return NULL;
            }
    }

    switch(key_size) {
        case sizeof(int8_t):
            switch(policy) {
                case HASH_SIMPLE: return hash_simple_int8;
                case HASH_ROBUST: return hash_robust_int8;
                case HASH_SECURE: return hash_secure_int8;
                default:
                    fprintf(stderr, "resolve_hash_func: invalid hash policy: %d\n", policy);
                    return NULL;
            }
        case sizeof(int16_t):
            switch(policy) {
                case HASH_SIMPLE: return hash_simple_int16;
                case HASH_ROBUST: return hash_robust_int16;
                case HASH_SECURE: return hash_secure_int16;
                default:
                    fprintf(stderr, "resolve_hash_func: invalid hash policy: %d\n", policy);
                    return NULL;
            }
        case sizeof(int32_t):
            switch(policy) {
                case HASH_SIMPLE: return hash_simple_int32;
                case HASH_ROBUST: return hash_robust_int32;
                case HASH_SECURE: return hash_secure_int32;
                default:
                    fprintf(stderr, "resolve_hash_func: invalid hash policy: %d\n", policy);
                    return NULL;
            }
        case sizeof(int64_t):
            switch(policy) {
                case HASH_SIMPLE: return hash_simple_int64;
                case HASH_ROBUST: return hash_robust_int64;
                case HASH_SECURE: return hash_secure_int64;
                default:
                    fprintf(stderr, "resolve_hash_func: invalid hash policy: %d\n", policy);
                    return NULL;
            }
        default:
            fprintf(stderr, "resolve_hash_func: unsupported key size: %zu\n", key_size);
        return NULL;
    }
}

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
) {
    if (num_buckets < 1 || key_size < 1 || !hash_func || !cmp || !hash_table_out) return CCOL_STATUS_INVALID_ARG;

    hash_table_t *hash_table = calloc(1, sizeof(hash_table_t));
    if (!hash_table) return CCOL_STATUS_ALLOC;

    ccol_status_t status = hash_table_init(hash_table);
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

    hash_table->policy = policy;
    hash_table->hash_func = hash_func;
    hash_table->copy_func = copy_func;
    hash_table->free_func = free_func;
    hash_table->print_func = print_func;

    hash_table->cmp = cmp;
    hash_table->ctx = ctx;

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

    hash_table->hash_func = NULL;
    hash_table->copy_func = NULL;
    hash_table->free_func = NULL;
    hash_table->print_func = NULL;
    hash_table->cmp = NULL;
    hash_table->ctx = NULL;

    hash_table->is_initialized = false;
}
