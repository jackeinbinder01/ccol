/*
 * ccol/comparator.c
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

#include <string.h>
#include "data_structures/comparator.h"

int cmp_int(const void *a, const void *b) {
    const int x = *(const int *)a;
    const int y = *(const int *)b;
    return (x > y) - (x < y);
}

int cmp_uint(const void *a, const void *b) {
    const unsigned int x = *(const unsigned int *)a;
    const unsigned int y = *(const unsigned int *)b;
    return (x > y) - (x < y);
}

int cmp_long(const void *a, const void *b) {
    const long x = *(const long *)a;
    const long y = *(const long *)b;
    return (x > y) - (x < y);
}

int cmp_long_long(const void *a, const void *b) {
    const long long x = *(const long long *)a;
    const long long y = *(const long long *)b;
    return (x > y) - (x < y);
}

int cmp_ulong(const void *a, const void *b) {
    const unsigned long x = *(const unsigned long *)a;
    const unsigned long y = *(const unsigned long *)b;
    return (x > y) - (x < y);
}

int cmp_ulong_long(const void *a, const void *b) {
    const unsigned long long x = *(const unsigned long long *)a;
    const unsigned long long y = *(const unsigned long long *)b;
    return (x > y) - (x < y);
}

int cmp_short(const void *a, const void *b) {
    const short x = *(const short *)a;
    const short y = *(const short *)b;
    return (x > y) - (x < y);
}

int cmp_ushort(const void *a, const void *b) {
    const unsigned short x = *(const unsigned short *)a;
    const unsigned short y = *(const unsigned short *)b;
    return (x > y) - (x < y);
}

int cmp_float(const void *a, const void *b) {
    const float x = *(const float *)a;
    const float y = *(const float *)b;
    return (x > y) - (x < y);
}

int cmp_double(const void *a, const void *b) {
    const double x = *(const double *)a;
    const double y = *(const double *)b;
    return (x > y) - (x < y);
}

int cmp_long_double(const void *a, const void *b) {
    const long double x = *(const long double *)a;
    const long double y = *(const long double *)b;
    return (x > y) - (x < y);
}

int cmp_char(const void *a, const void *b) {
    const char x = *(const char *)a;
    const char y = *(const char *)b;
    return (x > y) - (x < y);
}

int cmp_uchar(const void *a, const void *b) {
    const unsigned char x = *(const unsigned char *)a;
    const unsigned char y = *(const unsigned char *)b;
    return (x > y) - (x < y);
}

int cmp_string(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcmp(s1, s2);
}

int cmp_ptr(const void *a, const void *b) {
    const void *x = *(const void **)a;
    const void *y = *(const void **)b;
    return (x > y) - (x < y);
}
