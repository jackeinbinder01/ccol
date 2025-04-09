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

typedef enum {
    HASH_SIMPLE,
    HASH_ROBUST,
    HASH_SECURE,
} hash_policy_t;

typedef unsigned int (*hash_func_t)(const void *key);

unsigned int hash_int8(const void *key, hash_policy_t policy);
unsigned int hash_int16(const void *key, hash_policy_t policy);
unsigned int hash_int32(const void *key, hash_policy_t policy);
unsigned int hash_int64(const void *key, hash_policy_t policy);
unsigned int hash_uint8(const void *key, hash_policy_t policy);
unsigned int hash_uint16(const void *key, hash_policy_t policy);
unsigned int hash_uint32(const void *key, hash_policy_t policy);
unsigned int hash_uint64(const void *key, hash_policy_t policy);
unsigned int hash_string(const void *key, hash_policy_t policy);
unsigned int hash_ptr(const void *key, hash_policy_t policy);

#endif // HASH_H
