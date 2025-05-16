/*
 * ccol/src/hash/policies/simple.h
 *
 * Simple hash functions.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_HASH_SIMPLE_H
#define CCOL_HASH_SIMPLE_H

#include <stdint.h>

uint32_t ccol__hash_simple_uint8(const void *key, void *ctx);
uint32_t ccol__hash_simple_uint16(const void *key, void *ctx);
uint32_t ccol__hash_simple_uint32(const void *key, void *ctx);
uint32_t ccol__hash_simple_uint64(const void *key, void *ctx);
uint32_t ccol__hash_simple_str(const void *key, void *ctx);
uint32_t ccol__hash_simple_ptr(const void *key, void *ctx);

#endif  // CCOL_HASH_SIMPLE_H
