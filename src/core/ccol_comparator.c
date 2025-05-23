/*
 * ccol/src/core/cool_comparator.c
 *
 * Function wrapper for comparing data.
 *
 * Returns:
 *   < 0 if a < b
 *   = 0 if a == b
 *   > 0 if a > b
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <string.h>
#include <strings.h>
#include <stdint.h>

#include "ccol/ccol_comparator.h"
#include "ccol/ccol_hash.h"

int ccol_cmp_int8(const void *a, const void *b, void *ctx) {
	(void)ctx;
    int8_t x = *(const int8_t *)a;
    int8_t y = *(const int8_t *)b;
    return (x > y) - (x < y);
}

int ccol_cmp_int16(const void *a, const void *b, void *ctx) {
    (void)ctx;
    int16_t x = *(const int16_t *)a;
    int16_t y = *(const int16_t *)b;
    return (x > y) - (x < y);
}

int ccol_cmp_int32(const void *a, const void *b, void *ctx) {
    (void)ctx;
    int32_t x = *(const int32_t *)a;
    int32_t y = *(const int32_t *)b;
    return (x > y) - (x < y);
}

int ccol_cmp_int64(const void *a, const void *b, void *ctx) {
    (void)ctx;
    int64_t x = *(const int64_t *)a;
    int64_t y = *(const int64_t *)b;
    return (x > y) - (x < y);
}

int ccol_cmp_uint8(const void *a, const void *b, void *ctx) {
	(void)ctx;
    uint8_t x = *(const uint8_t *)a;
    uint8_t y = *(const uint8_t *)b;
    return (x > y) - (x < y);
}

int ccol_cmp_uint16(const void *a, const void *b, void *ctx) {
    (void)ctx;
    uint16_t x = *(const uint16_t *)a;
    uint16_t y = *(const uint16_t *)b;
    return (x > y) - (x < y);
}

int ccol_cmp_uint32(const void *a, const void *b, void *ctx) {
    (void)ctx;
    uint32_t x = *(const uint32_t *)a;
    uint32_t y = *(const uint32_t *)b;
    return (x > y) - (x < y);
}

int ccol_cmp_uint64(const void *a, const void *b, void *ctx) {
    (void)ctx;
    uint64_t x = *(const uint64_t *)a;
    uint64_t y = *(const uint64_t *)b;
    return (x > y) - (x < y);
}

int ccol_cmp_float(const void *a, const void *b, void *ctx) {
	(void)ctx;
    float x = *(const float *)a;
    float y = *(const float *)b;

    if (x < y) return -1;
    if (x > y || x != y) return 1;
    return 0;
}

int ccol_cmp_double(const void *a, const void *b, void *ctx) {
	(void)ctx;
    double x = *(const double *)a;
    double y = *(const double *)b;

    if (x < y) return -1;
    if (x > y || x != y) return 1;
    return 0;
}

int ccol_cmp_long_double(const void *a, const void *b, void *ctx) {
	(void)ctx;
    long double x = *(const long double *)a;
    long double y = *(const long double *)b;

    if (x < y) return -1;
    if (x > y || x != y) return 1;
    return 0;
}

int ccol_cmp_str(const void *a, const void *b, void *ctx) {
	(void)ctx;
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcmp(s1, s2);
}

int ccol_cmp_str_case_insensitive(const void *a, const void *b, void *ctx) {
	(void)ctx;
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcasecmp(s1, s2);
}

int ccol_cmp_ptr(const void *a, const void *b, void *ctx) {
	(void)ctx;
    const void *x = *(const void **)a;
    const void *y = *(const void **)b;
    return (x > y) - (x < y);
}

int ccol_cmp_hash_entry_key(const void *entry_ptr, const void *key_ptr, void *ctx) {
	const ccol_hash_entry_t *entry = (const ccol_hash_entry_t *)entry_ptr;
    const ccol_comparator_t *cmp_key = (const ccol_comparator_t *)ctx;

    return cmp_key->func(entry->key, key_ptr, cmp_key->ctx);
}

