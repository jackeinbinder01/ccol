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

unsigned int hash_robust_int8(const void *key);
unsigned int hash_robust_int16(const void *key);
unsigned int hash_robust_int32(const void *key);
unsigned int hash_robust_int64(const void *key);
unsigned int hash_robust_uint8(const void *key);
unsigned int hash_robust_uint16(const void *key);
unsigned int hash_robust_uint32(const void *key);
unsigned int hash_robust_uint64(const void *key);
unsigned int hash_robust_string(const void *key);
unsigned int hash_robust_ptr(const void *key);
