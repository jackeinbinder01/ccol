/*
 * ccol/src/hash/ccol_hash.c
 *
 * Hash functions with context and policy support.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "ccol/ccol_hash.h"
#include "ccol/ccol_constants.h"
#include "ccol/ccol_status.h"

#include "simple.h"
#include "robust.h"
#include "secure.h"

static ccol_status_t ccol_resolve_hash_func(
    size_t key_size,
    ccol_hash_policy_t policy,
    ccol_hash_func_t *hash_func_out
) {
    if (policy == CCOL_HASH_CUSTOM) {
        *hash_func_out = NULL;
        return CCOL_STATUS_OK;
    }
    if (policy < CCOL_HASH_SIMPLE || policy > CCOL_HASH_SECURE) return CCOL_STATUS_HASH_POLICY;

    if (key_size == CCOL_HASH_KEY_STRING) {
        switch(policy) {
            case CCOL_HASH_SIMPLE: *hash_func_out = ccol__hash_simple_str; return CCOL_STATUS_OK;
            case CCOL_HASH_ROBUST: *hash_func_out = ccol__hash_robust_str; return CCOL_STATUS_OK;
            case CCOL_HASH_SECURE: *hash_func_out = ccol__hash_secure_str; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    if (key_size == sizeof(int8_t) || key_size == sizeof(uint8_t)) {
        switch(policy) {
            case CCOL_HASH_SIMPLE: *hash_func_out = ccol__hash_simple_uint8; return CCOL_STATUS_OK;
            case CCOL_HASH_ROBUST: *hash_func_out = ccol__hash_robust_uint8; return CCOL_STATUS_OK;
            case CCOL_HASH_SECURE: *hash_func_out = ccol__hash_secure_uint8; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    if (key_size == sizeof(int16_t) || key_size == sizeof(uint16_t)) {
        switch(policy) {
            case CCOL_HASH_SIMPLE: *hash_func_out = ccol__hash_simple_uint16; return CCOL_STATUS_OK;
            case CCOL_HASH_ROBUST: *hash_func_out = ccol__hash_robust_uint16; return CCOL_STATUS_OK;
            case CCOL_HASH_SECURE: *hash_func_out = ccol__hash_secure_uint16; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    if (key_size == sizeof(int32_t) || key_size == sizeof(uint32_t)) {
        switch(policy) {
            case CCOL_HASH_SIMPLE: *hash_func_out = ccol__hash_simple_uint32; return CCOL_STATUS_OK;
            case CCOL_HASH_ROBUST: *hash_func_out = ccol__hash_robust_uint32; return CCOL_STATUS_OK;
            case CCOL_HASH_SECURE: *hash_func_out = ccol__hash_secure_uint32; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    if (key_size == sizeof(int64_t) || key_size == sizeof(uint64_t)) {
        switch(policy) {
            case CCOL_HASH_SIMPLE: *hash_func_out = ccol__hash_simple_uint64; return CCOL_STATUS_OK;
            case CCOL_HASH_ROBUST: *hash_func_out = ccol__hash_robust_uint64; return CCOL_STATUS_OK;
            case CCOL_HASH_SECURE: *hash_func_out = ccol__hash_secure_uint64; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    if (key_size == sizeof(void *)) {
        switch(policy) {
            case CCOL_HASH_SIMPLE: *hash_func_out = ccol__hash_simple_ptr; return CCOL_STATUS_OK;
            case CCOL_HASH_ROBUST: *hash_func_out = ccol__hash_robust_ptr; return CCOL_STATUS_OK;
            case CCOL_HASH_SECURE: *hash_func_out = ccol__hash_secure_ptr; return CCOL_STATUS_OK;
            default: return CCOL_STATUS_HASH_POLICY;
        }
    }

    *hash_func_out = NULL;
    return CCOL_STATUS_KEY_SIZE;
}

ccol_status_t ccol_hash_create_from_policy(
    size_t key_size,
    ccol_hash_policy_t policy,
    void *ctx,
    ccol_hash_t *hasher_out) {
    if (!hasher_out) return CCOL_STATUS_INVALID_ARG;
    if (policy == CCOL_HASH_CUSTOM) return CCOL_STATUS_HASH_POLICY;

    ccol_hash_func_t resolved_func = NULL;
    ccol_status_t status = ccol_resolve_hash_func(key_size, policy, &resolved_func);
    if (status != CCOL_STATUS_OK) return status;

    *hasher_out = ccol_hash_create(resolved_func, ctx, policy);
    return CCOL_STATUS_OK;
}
