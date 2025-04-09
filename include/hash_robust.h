/*
 * ccol/hash_robust.h
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef HASH_ROBUST_H
#define HASH_ROBUST_H

#include "hash.h"

unsigned int hash_robust_int8(const void *key);
unsigned int hash_robust_int16(const void *key);
unsigned int hash_robust_int32(const void *key);
unsigned int hash_robust_int64(const void *key);
unsigned int hash_robust_uint8(const void *key);
unsigned int hash_robust_uint16(const void *key);
unsigned int hash_robust_uint32(const void *key);
unsigned int hash_robust_uint64(const void *key);
unsigned int hash_robust_str(const void *key);
unsigned int hash_robust_ptr(const void *key);

#endif // HASH_ROBUST_H
