/*
 * ccol/hash.h
 *
 * Hash functions for all primitives.
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef HASH_H
#define HASH_H

#include <stddef.h>

typedef unsigned int (*hash_func_t)(const void *key);

unsigned int hash_int(const void *key);
unsigned int hash_uint(const void *key);
unsigned int hash_long(const void *key);
unsigned int hash_long_long(const void *key);
unsigned int hash_ulong(const void *key);
unsigned int hash_ulong_long(const void *key);
unsigned int hash_short(const void *key);
unsigned int hash_ushort(const void *key);
unsigned int hash_char(const void *key);
unsigned int hash_uchar(const void *key);
unsigned int hash_string(const void *key);
unsigned int hash_ptr(const void *key);

#endif // HASH_H
