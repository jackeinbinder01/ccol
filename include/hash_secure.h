/*
 * ccol/hash_secure.h
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef HASH_SECURE_H
#define HASH_SECURE_H

#include "hash.h"

unsigned int hash_secure_int8(const void *key);
unsigned int hash_secure_int16(const void *key);
unsigned int hash_secure_int32(const void *key);
unsigned int hash_secure_int64(const void *key);
unsigned int hash_secure_uint8(const void *key);
unsigned int hash_secure_uint16(const void *key);
unsigned int hash_secure_uint32(const void *key);
unsigned int hash_secure_uint64(const void *key);
unsigned int hash_secure_string(const void *key);
unsigned int hash_secure_ptr(const void *key);

#endif // HASH_SECURE_H
