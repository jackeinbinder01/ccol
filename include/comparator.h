/*
 * ccol/comparator.h
 *
 * Comparators for all primitives.
 *
 * Returns:
 *   < 0 if a < b
 *   = 0 if a == b
 *   > 0 if a > b
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "ccol_constants.h"

int cmp_int8(const void *a, const void *b, void *ctx);
int cmp_int16(const void *a, const void *b, void *ctx);
int cmp_int32(const void *a, const void *b, void *ctx);
int cmp_int64(const void *a, const void *b, void *ctx);
int cmp_uint8(const void *a, const void *b, void *ctx);
int cmp_uint16(const void *a, const void *b, void *ctx);
int cmp_uint32(const void *a, const void *b, void *ctx);
int cmp_uint64(const void *a, const void *b, void *ctx);

int cmp_float(const void *a, const void *b, void *ctx);
int cmp_double(const void *a, const void *b, void *ctx);
int cmp_long_double(const void *a, const void *b, void *ctx);

int cmp_str(const void *a, const void *b, void *ctx);
int cmp_str_case_insensitive(const void *a, const void *b, void *ctx);
int cmp_ptr(const void *a, const void *b, void *ctx);
int cmp_hash_keys(const void *entry_ptr, const void *key_ptr, void *ctx);

#endif // COMPARATOR_H
