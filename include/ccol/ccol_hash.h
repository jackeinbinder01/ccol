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

typedef struct ccol_hash_entry {
    void *key;
    void *value;
} ccol_hash_entry_t;

typedef enum ccol_hash_policy {
    CCOL_HASH_SIMPLE = 1,
    CCOL_HASH_ROBUST = 2,
    CCOL_HASH_SECURE = 3,
    CCOL_HASH_CUSTOM = 4
} ccol_hash_policy_t;

static inline const char * ccol_hash_policy_to_string(ccol_hash_policy_t policy) {
    switch (policy) {
        case CCOL_HASH_SIMPLE:    return "CCOL_HASH_SIMPLE";
        case CCOL_HASH_ROBUST:    return "CCOL_HASH_ROBUST";
        case CCOL_HASH_SECURE:    return "CCOL_HASH_SECURE";
        case CCOL_HASH_CUSTOM:    return "CCOL_HASH_CUSTOM";
        default:                  return "INVALID";
    }
}

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

const char *ccol_hash_policy_to_str(ccol_hash_policy_t policy);

#endif  // CCOL_HASH_H
