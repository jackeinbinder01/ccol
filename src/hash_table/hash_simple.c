/*
 * ccol/hash_simple_simple.c
 *
 * Simple hash functions
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdint.h>
#include "hash.h"
#include "hash_simple.h"

uint32_t hash_simple_int8(const void *key) {
    const int8_t x = *(const int8_t*)key;
    return (uint8_t)x ^ ((uint8_t)x >> 4);
}

uint32_t hash_simple_int16(const void *key) {
    const int16_t x = *(const int16_t*)key;
    return (uint16_t)x ^ ((uint16_t)x >> 8);
}

uint32_t hash_simple_int32(const void *key) {
    const int32_t x = *(const int32_t*)key;
    return (uint32_t)x ^ ((uint32_t)x >> 16);
}

uint32_t hash_simple_int64(const void *key) {
    const int64_t x = *(const int64_t*)key;
    return (uint64_t)x ^ ((uint64_t)x >> 32);
}

uint32_t hash_simple_uint8(const void *key) {
    const uint8_t x = *(const uint8_t*)key;
    return x ^ (x >> 4);
}

uint32_t hash_simple_uint16(const void *key) {
    const uint16_t x = *(const uint16_t*)key;
    return x ^ (x >> 8);
}

uint32_t hash_simple_uint32(const void *key) {
    const uint32_t x = *(const uint32_t*)key;
    return x ^ (x >> 16);
}

uint32_t hash_simple_uint64(const void *key) {
    const uint64_t x = *(const uint64_t*)key;
    return x ^ (x >> 32);
}

uint32_t hash_simple_str(const void *key) {
    const char *str = *(const char **)key;
    uint32_t hash = 5381;
    int c;

    while ((c = *str++)) {
      hash = (hash << 5) + hash + (unsigned char)(*str);
    }

    return hash;
}

uint32_t hash_simple_ptr(const void *key) {
    const uintptr_t ptr = (uintptr_t)key;
    return (uint32_t)(ptr ^ (ptr >> 32));
}

