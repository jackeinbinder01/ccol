/*
 * ccol/ccol_comparator.h
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

#ifndef CCOL_COMPARATOR_H
#define CCOL_COMPARATOR_H

#include "ccol_constants.h"

typedef int (*ccol_comparator_func_t)(const void *a, const void *b, void *ctx);

typedef struct ccol_comparator {
    ccol_comparator_func_t func;
    void *ctx;
} ccol_comparator_t;

static inline ccol_comparator_t ccol_comparator_create(ccol_comparator_func_t func, void *ctx) {
    ccol_comparator_t cmp = { .func = func, .ctx = ctx };
    return cmp;
}

int ccol_cmp_int8(const void *a, const void *b, void *ctx);
int ccol_cmp_int16(const void *a, const void *b, void *ctx);
int ccol_cmp_int32(const void *a, const void *b, void *ctx);
int ccol_cmp_int64(const void *a, const void *b, void *ctx);
int ccol_cmp_uint8(const void *a, const void *b, void *ctx);
int ccol_cmp_uint16(const void *a, const void *b, void *ctx);
int ccol_cmp_uint32(const void *a, const void *b, void *ctx);
int ccol_cmp_uint64(const void *a, const void *b, void *ctx);

int ccol_cmp_float(const void *a, const void *b, void *ctx);
int ccol_cmp_double(const void *a, const void *b, void *ctx);
int ccol_cmp_long_double(const void *a, const void *b, void *ctx);

int ccol_cmp_str(const void *a, const void *b, void *ctx);
int ccol_cmp_str_case_insensitive(const void *a, const void *b, void *ctx);

int ccol_cmp_ptr(const void *a, const void *b, void *ctx);
int ccol_cmp_hash_entry_key(const void *entry_ptr, const void *key_ptr, void *ctx);

#endif  // CCOL_COMPARATOR_H
