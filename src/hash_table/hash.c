/*
 * ccol/hash.h
 *
 * Hash functions for all primitives.
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#include "hash.h"
#include "hash_simple.h"
#include "hash_secure.h"
#include "hash_robust.h"

unsigned int hash_int8(const void *key, hash_policy_t policy) {
    switch (policy) {
      case HASH_SIMPLE: return hash_simple_int8(key);
      case HASH_ROBUST: return hash_robust_int8(key);
      case HASH_SECURE: return hash_secure_int8(key);
    }
}

unsigned int hash_int16(const void *key, hash_policy_t policy) {
    switch (policy) {
      case HASH_SIMPLE: return hash_simple_int16(key);
      case HASH_ROBUST: return hash_robust_int16(key);
      case HASH_SECURE: return hash_secure_int16(key);
    }
}

unsigned int hash_int32(const void *key, hash_policy_t policy) {
    switch (policy) {
      case HASH_SIMPLE: return hash_simple_int32(key);
      case HASH_ROBUST: return hash_robust_int32(key);
      case HASH_SECURE: return hash_secure_int32(key);
    }
}

unsigned int hash_int64(const void *key, hash_policy_t policy) {
    switch (policy) {
      case HASH_SIMPLE: return hash_simple_int64(key);
      case HASH_ROBUST: return hash_robust_int64(key);
      case HASH_SECURE: return hash_secure_int64(key);
    }
}

unsigned int hash_uint8(const void *key, hash_policy_t policy) {
    switch (policy) {
      case HASH_SIMPLE: return hash_simple_uint8(key);
      case HASH_ROBUST: return hash_robust_uint8(key);
      case HASH_SECURE: return hash_secure_uint8(key);
    }
}

unsigned int hash_uint16(const void *key, hash_policy_t policy) {
    switch (policy) {
      case HASH_SIMPLE: return hash_simple_uint16(key);
      case HASH_ROBUST: return hash_robust_uint16(key);
      case HASH_SECURE: return hash_secure_uint16(key);
    }
}

unsigned int hash_uint32(const void *key, hash_policy_t policy) {
    switch (policy) {
      case HASH_SIMPLE: return hash_simple_uint32(key);
      case HASH_ROBUST: return hash_robust_uint32(key);
      case HASH_SECURE: return hash_secure_uint32(key);
    }
}

unsigned int hash_uint64(const void *key, hash_policy_t policy) {
    switch (policy) {
      case HASH_SIMPLE: return hash_simple_uint64(key);
      case HASH_ROBUST: return hash_robust_uint64(key);
      case HASH_SECURE: return hash_secure_uint64(key);
    }
}

unsigned int hash_string(const void *key, hash_policy_t policy) {
    switch (policy) {
      case HASH_SIMPLE: return hash_simple_string(key);
      case HASH_ROBUST: return hash_robust_string(key);
      case HASH_SECURE: return hash_secure_string(key);
    }
}

unsigned int hash_ptr(const void *key, hash_policy_t policy) {
    switch (policy) {
      case HASH_SIMPLE: return hash_simple_ptr(key);
      case HASH_ROBUST: return hash_robust_ptr(key);
      case HASH_SECURE: return hash_secure_ptr(key);
    }
}
