/*
 * ccol/hash.h
 *
 * Hash functions for all primitives.
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#include <stdint.h>

#include "hash.h"
#include "hash_simple.h"
#include "hash_secure.h"
#include "hash_robust.h"

uint32_t hash_int8(const void *key, void *ctx) {
    hash_policy_t policy = ((hash_policy_ctx_t *)ctx)->policy;
    switch (policy) {
        case HASH_SIMPLE: return hash_simple_int8(key);
        case HASH_ROBUST: return hash_robust_int8(key);
        case HASH_SECURE: return hash_secure_int8(key);
        default: return 0;
    }
}

uint32_t hash_int16(const void *key, void *ctx) {
    hash_policy_t policy = ((hash_policy_ctx_t *)ctx)->policy;
    switch (policy) {
        case HASH_SIMPLE: return hash_simple_int16(key);
        case HASH_ROBUST: return hash_robust_int16(key);
        case HASH_SECURE: return hash_secure_int16(key);
        default: return 0;
    }
}

uint32_t hash_int32(const void *key, void *ctx) {
    hash_policy_t policy = ((hash_policy_ctx_t *)ctx)->policy;
    switch (policy) {
        case HASH_SIMPLE: return hash_simple_int32(key);
        case HASH_ROBUST: return hash_robust_int32(key);
        case HASH_SECURE: return hash_secure_int32(key);
        default: return 0;
    }
}

uint32_t hash_int64(const void *key, void *ctx) {
    hash_policy_t policy = ((hash_policy_ctx_t *)ctx)->policy;
    switch (policy) {
        case HASH_SIMPLE: return hash_simple_int64(key);
        case HASH_ROBUST: return hash_robust_int64(key);
        case HASH_SECURE: return hash_secure_int64(key);
        default: return 0;
    }
}

uint32_t hash_uint8(const void *key, void *ctx) {
    hash_policy_t policy = ((hash_policy_ctx_t *)ctx)->policy;
    switch (policy) {
        case HASH_SIMPLE: return hash_simple_uint8(key);
        case HASH_ROBUST: return hash_robust_uint8(key);
        case HASH_SECURE: return hash_secure_uint8(key);
        default: return 0;
    }
}

uint32_t hash_uint16(const void *key, void *ctx) {
    hash_policy_t policy = ((hash_policy_ctx_t *)ctx)->policy;
    switch (policy) {
        case HASH_SIMPLE: return hash_simple_uint16(key);
        case HASH_ROBUST: return hash_robust_uint16(key);
        case HASH_SECURE: return hash_secure_uint16(key);
        default: return 0;
    }
}

uint32_t hash_uint32(const void *key, void *ctx) {
    hash_policy_t policy = ((hash_policy_ctx_t *)ctx)->policy;
    switch (policy) {
        case HASH_SIMPLE: return hash_simple_uint32(key);
        case HASH_ROBUST: return hash_robust_uint32(key);
        case HASH_SECURE: return hash_secure_uint32(key);
        default: return 0;
    }
}

uint32_t hash_uint64(const void *key, void *ctx) {
    hash_policy_t policy = ((hash_policy_ctx_t *)ctx)->policy;
    switch (policy) {
        case HASH_SIMPLE: return hash_simple_uint64(key);
        case HASH_ROBUST: return hash_robust_uint64(key);
        case HASH_SECURE: return hash_secure_uint64(key);
        default: return 0;
    }
}

uint32_t hash_str(const void *key, void *ctx) {
    hash_policy_t policy = ((hash_policy_ctx_t *)ctx)->policy;
    switch (policy) {
        case HASH_SIMPLE: return hash_simple_str(key);
        case HASH_ROBUST: return hash_robust_str(key);
        case HASH_SECURE: return hash_secure_str(key);
        default: return 0;
    }
}

uint32_t hash_ptr(const void *key, void *ctx) {
    hash_policy_t policy = ((hash_policy_ctx_t *)ctx)->policy;
    switch (policy) {
        case HASH_SIMPLE: return hash_simple_ptr(key);
        case HASH_ROBUST: return hash_robust_ptr(key);
        case HASH_SECURE: return hash_secure_ptr(key);
        default: return 0;
    }
}
