/*
 * ccol/src/hash/policies/robust.h
 *
 * Robust hash functions.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_HASH_ROBUST_H
#define CCOL_HASH_ROBUST_H

#include <stdint.h>

uint32_t ccol__hash_robust_uint8(const void *key, void *ctx);
uint32_t ccol__hash_robust_uint16(const void *key, void *ctx);
uint32_t ccol__hash_robust_uint32(const void *key, void *ctx);
uint32_t ccol__hash_robust_uint64(const void *key, void *ctx);
uint32_t ccol__hash_robust_str(const void *key, void *ctx);
uint32_t ccol__hash_robust_ptr(const void *key, void *ctx);

#endif  // CCOL_HASH_ROBUST_H
