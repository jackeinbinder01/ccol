/*
 * col/src/hash/policies/secure.h
 *
 * Secure hash functions.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_HASH_SECURE_H
#define CCOL_HASH_SECURE_H

#include <stdint.h>

uint32_t ccol__hash_secure_uint8(const void *key, void *ctx);
uint32_t ccol__hash_secure_uint16(const void *key, void *ctx);
uint32_t ccol__hash_secure_uint32(const void *key, void *ctx);
uint32_t ccol__hash_secure_uint64(const void *key, void *ctx);
uint32_t ccol__hash_secure_str(const void *key, void *ctx);
uint32_t ccol__hash_secure_ptr(const void *key, void *ctx);

#endif  // CCOL_HASH_SECURE_H
