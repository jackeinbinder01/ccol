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

typedef int (*comparator_t)(const void *, const void *);

int cmp_int(const void *a, const void *b);
int cmp_uint(const void *a, const void *b);
int cmp_long(const void *a, const void *b);
int cmp_long_long(const void *a, const void *b);
int cmp_ulong(const void *a, const void *b);
int cmp_ulong_long(const void *a, const void *b);
int cmp_short(const void *a, const void *b);
int cmp_ushort(const void *a, const void *b);
int cmp_float(const void *a, const void *b);
int cmp_double(const void *a, const void *b);
int cmp_long_double(const void *a, const void *b);
int cmp_char(const void *a, const void *b);
int cmp_uchar(const void *a, const void *b);
int cmp_string(const void *a, const void *b);
int cmp_ptr(const void *a, const void *b);

#endif // COMPARATOR_H
