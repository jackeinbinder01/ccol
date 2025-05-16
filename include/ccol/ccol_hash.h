/*
 * ccol/ccol_hash.h
 *
 * Hash wrapper with context and policy support.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_HASH_H
#define CCOL_HASH_H

#include <stddef.h>
#include <stdint.h>

#include "ccol_status.h"

typedef enum ccol_hash_policy {
    HASH_SIMPLE = 1,
    HASH_ROBUST = 2,
    HASH_SECURE = 3,
    HASH_CUSTOM = 4,
} ccol_hash_policy_t;

typedef uint32_t (*ccol_hash_func_t)(const void *key, void *ctx);

typedef struct {
    ccol_hash_func_t func;
    void *ctx;
    ccol_hash_policy_t policy;
} ccol_hash_t;

static inline ccol_hash_t ccol_hash_create(ccol_hash_func_t func, void *ctx, ccol_hash_policy_t policy) {
    return (ccol_hash_t){ .func = func, .ctx = ctx, .policy = policy };
}

ccol_status_t ccol_resolve_hash_func(size_t key_size, ccol_hash_policy_t policy, ccol_hash_func_t *hash_func_out);
ccol_status_t ccol_hash_create_from_policy(
    size_t key_size,
    ccol_hash_policy_t policy,
    void *ctx,
    ccol_hash_t *hasher_out
);

uint32_t ccol_hash_int8(const void *key, void *ctx);
uint32_t ccol_hash_int16(const void *key, void *ctx);
uint32_t ccol_hash_int32(const void *key, void *ctx);
uint32_t ccol_hash_int64(const void *key, void *ctx);

uint32_t ccol_hash_uint8(const void *key, void *ctx);
uint32_t ccol_hash_uint16(const void *key, void *ctx);
uint32_t ccol_hash_uint32(const void *key, void *ctx);
uint32_t ccol_hash_uint64(const void *key, void *ctx);

uint32_t ccol_hash_str(const void *key, void *ctx);
uint32_t ccol_hash_ptr(const void *key, void *ctx);

const char *ccol_hash_policy_to_str(ccol_hash_policy_t policy);

#endif  // CCOL_HASH_H
