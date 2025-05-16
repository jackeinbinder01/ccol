/*
 * ccol/src/hash/policies/simple.c
 *
 * Simple hash function implementations.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdint.h>

#include "simple.h"

uint32_t ccol__hash_simple_uint8(const void *key, void *ctx) {
    (void)ctx;
    const uint8_t x = *(const uint8_t*)key;
    return x ^ (x >> 4);
}

uint32_t ccol__hash_simple_uint16(const void *key, void *ctx) {
    (void)ctx;
    const uint16_t x = *(const uint16_t*)key;
    return x ^ (x >> 8);
}

uint32_t ccol__hash_simple_uint32(const void *key, void *ctx) {
    (void)ctx;
    const uint32_t x = *(const uint32_t*)key;
    return x ^ (x >> 16);
}

uint32_t ccol__hash_simple_uint64(const void *key, void *ctx) {
    (void)ctx;
    const uint64_t x = *(const uint64_t*)key;
    return x ^ (x >> 32);
}

uint32_t ccol__hash_simple_str(const void *key, void *ctx) {
    (void)ctx;
    const char *str = *(const char **)key;
    if (!str) return 0;
    uint32_t ccol__hash = 5381;
    int c;

    while ((c = *str++)) {
      hash = (hash << 5) + hash + c;
    }

    return hash;
}

uint32_t ccol__hash_simple_ptr(const void *key, void *ctx) {
    (void)ctx;
    const uintptr_t ptr = (uintptr_t)key;
    return (uint32_t)(ptr ^ (ptr >> 32));
}

