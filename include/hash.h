/*
 * ccol/hash.h
 *
 * Hash functions for all primitives.
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdint.h>

#include "ccol_status.h"

typedef enum {
    HASH_SIMPLE = 1,
    HASH_ROBUST = 2,
    HASH_SECURE = 3,
    HASH_CUSTOM = 4,
} hash_policy_t;

typedef uint32_t (*hash_func_t)(const void *key, void *ctx);

typedef struct {
    hash_func_t func;
    void *ctx;
    hash_policy_t policy;
} hash_t;

static inline hash_t hash_create(hash_func_t func, void *ctx, hash_policy_t policy) {
    return (hash_t){ .func = func, .ctx = ctx };
}

ccol_status_t resolve_hash_func(size_t key_size, hash_policy_t policy, hash_func_t *hash_func_out);
ccol_status_t hash_create_from_policy(size_t key_size, hash_policy_t policy, void *ctx, hash_t *hasher_out);

uint32_t hash_int8(const void *key, void *ctx);
uint32_t hash_int16(const void *key, void *ctx);
uint32_t hash_int32(const void *key, void *ctx);
uint32_t hash_int64(const void *key, void *ctx);

uint32_t hash_uint8(const void *key, void *ctx);
uint32_t hash_uint16(const void *key, void *ctx);
uint32_t hash_uint32(const void *key, void *ctx);
uint32_t hash_uint64(const void *key, void *ctx);

uint32_t hash_str(const void *key, void *ctx);
uint32_t hash_ptr(const void *key, void *ctx);

const char *hash_policy_to_str(hash_policy_t policy);

#endif // HASH_H
