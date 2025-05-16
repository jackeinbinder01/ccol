/*
 * ccol/hash_robust.c
 *
 * Robust hash functions
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdint.h>

#include "hash.h"
#include "hash_robust.h"

uint32_t hash_robust_uint8(const void *key, void *ctx);
uint32_t hash_robust_uint16(const void *key, void *ctx);
uint32_t hash_robust_uint32(const void *key, void *ctx);
uint32_t hash_robust_uint64(const void *key, void *ctx);
uint32_t hash_robust_str(const void *key, void *ctx);
uint32_t hash_robust_ptr(const void *key, void *ctx);
