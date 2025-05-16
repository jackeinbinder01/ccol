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

unsigned int hash_secure_uint8(const void *key, void *ctx);
unsigned int hash_secure_uint16(const void *key, void *ctx);
unsigned int hash_secure_uint32(const void *key, void *ctx);
unsigned int hash_secure_uint64(const void *key, void *ctx);
unsigned int hash_secure_str(const void *key, void *ctx);
unsigned int hash_secure_ptr(const void *key, void *ctx);

#endif // HASH_SECURE_H
