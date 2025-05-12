/*
 * ccol/hash.h
 *
 *
 * Created by Jack:
 *
 * Copyright (C) 2025 Jack
 *
 */
#include "hash.h"
#include "hash_simple.h"
#include "hash_robust.h"
#include "hash_secure.h"
#include "ccol_constants.h"
#include "ccol_status.h"

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

ccol_status_t hash_create_from_policy(size_t key_size, hash_policy_t policy, void *ctx, hash_t *hasher_out) {
    if (!hasher_out) return CCOL_STATUS_INVALID_ARG;
    if (policy == HASH_CUSTOM) return CCOL_STATUS_HASH_POLICY;

    hash_func_t resolved_func = NULL;
    ccol_status_t status = resolve_hash_func(key_size, policy, &resolved_func);
    if (status != CCOL_STATUS_OK) return status;

    *hasher_out = hash_create(resolved_func, ctx, policy);
    return CCOL_STATUS_OK;
}
