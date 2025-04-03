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

unsigned int hash_int(const void *key) {
    const int32_t x = *(const int *)key;
    const uint32_t ux = (uint32_t)x;
    return ux ^ (ux >> 16);
}

unsigned int hash_uint(const void *key);

unsigned int hash_long(const void *key) {
    const int64_t x = *(const long *)key;
    const uint64_t ux = (uint64_t)x;
    return (unsigned int)(ux ^ (ux >> 32));
}

unsigned int hash_long_long(const void *key) {
    const long long x = *(const long long *)key;
    return (unsigned int)(x ^ (x >> 31));
}

unsigned int hash_ulong(const void *key) {
    const unsigned long x = *(const unsigned long *)key;
    return (unsigned int)(x ^ (x >> 32));
}
unsigned int hash_ulong_long(const void *key) {
    const unsigned long long x = *(const unsigned long long *)key;
    return (unsigned int)(x ^ (x >> 32));
}

unsigned int hash_short(const void *key);
unsigned int hash_ushort(const void *key);
unsigned int hash_char(const void *key);
unsigned int hash_uchar(const void *key);
unsigned int hash_string(const void *key);

unsigned int hash_ptr(const void *key) {
    uintptr_t addr = (uintptr_t)key;
    return (unsigned int)(addr ^ (addr >> 32));
}

