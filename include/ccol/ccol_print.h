/*
 * ccol/ccol_print.h
 *
 * Function wrappers for printing values with printf-style handlers.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_PRINT_H
#define CCOL_PRINT_H

#include <stddef.h>

#include "ccol_constants.h"

typedef struct ccol_print {
    ccol_print_func_t func;
    void *ctx;
} ccol_print_t;

static inline ccol_print_t ccol_print_create(ccol_print_func_t func, void *ctx) {
    return (ccol_print_t){ .func = func, .ctx = ctx };
}

void ccol_print_int8(const void *x, void *ctx);
void ccol_print_int16(const void *x, void *ctx);
void ccol_print_int32(const void *x, void *ctx);
void ccol_print_int64(const void *x, void *ctx);

void ccol_print_uint8(const void *x, void *ctx);
void ccol_print_uint16(const void *x, void *ctx);
void ccol_print_uint32(const void *x, void *ctx);
void ccol_print_uint64(const void *x, void *ctx);

void ccol_print_float(const void *x, void *ctx);
void ccol_print_double(const void *x, void *ctx);
void ccol_print_long_double(const void *x, void *ctx);

void ccol_print_string(const void *x, void *ctx);

#endif  // CCOL_PRINT_H
