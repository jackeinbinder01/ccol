/*
 * ccol/hash_simple.h
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef HASH_SIMPLE_H
#define HASH_SIMPLE_H

#include "hash.h"

unsigned int hash_simple_int8(const void *key);
unsigned int hash_simple_int16(const void *key);
unsigned int hash_simple_int32(const void *key);
unsigned int hash_simple_int64(const void *key);
unsigned int hash_simple_uint8(const void *key);
unsigned int hash_simple_uint16(const void *key);
unsigned int hash_simple_uint32(const void *key);
unsigned int hash_simple_uint64(const void *key);
unsigned int hash_simple_string(const void *key);
unsigned int hash_simple_ptr(const void *key);

#endif // HASH_SIMPLE_H
