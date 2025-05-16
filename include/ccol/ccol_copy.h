/*
 * ccol/ccol_copy.h
 *
 * Function wrapper for deep and shallow copying.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_COPY_H
#define CCOL_COPY_H

#include "ccol_constants.h"

typedef struct ccol_copy {
    ccol_copy_func_t func;
    void *ctx;
} ccol_copy_t;

static inline ccol_copy_t ccol_copy_create(ccol_copy_func_t func, void *ctx) {
    return (ccol_copy_t){ .func = func, .ctx = ctx };
}

void *ccol_copy_int8(const void *data, void *ctx);
void *ccol_copy_int16(const void *data, void *ctx);
void *ccol_copy_int32(const void *data, void *ctx);
void *ccol_copy_int64(const void *data, void *ctx);

void *ccol_copy_uint8(const void *data, void *ctx);
void *ccol_copy_uint16(const void *data, void *ctx);
void *ccol_copy_uint32(const void *data, void *ctx);
void *ccol_copy_uint64(const void *data, void *ctx);

void *ccol_copy_str(const void *data, void *ctx); // Deep copy of null-terminated string
void *ccol_copy_identity(const void *data, void *ctx); // Shallow copy (returns passed object)

#endif  // CCOL_COPY_H
