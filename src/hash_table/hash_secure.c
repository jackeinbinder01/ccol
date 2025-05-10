/*
 * ccol/hash_secure.c
 *
 * Secure hash functions
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdint.h>
#include "hash.h"
#include "hash_secure.h"

uint32_t hash_secure_int8(const void *key);
uint32_t hash_secure_int16(const void *key);
uint32_t hash_secure_int32(const void *key);
uint32_t hash_secure_int64(const void *key);
uint32_t hash_secure_uint8(const void *key);
uint32_t hash_secure_uint16(const void *key);
uint32_t hash_secure_uint32(const void *key);
uint32_t hash_secure_uint64(const void *key);
uint32_t hash_secure_str(const void *key);
uint32_t hash_secure_ptr(const void *key);
