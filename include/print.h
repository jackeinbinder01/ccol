/*
 * ccol/print.h
 *
 * Print functions for all primitives
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef PRINT_H
#define PRINT_H

#include "ccol_constants.h"

typedef struct {
    print_func_t func;
    void *ctx;
} print_t;

static inline print_t print_create(print_func_t func, void *ctx) {
    return (print_t){ .func = func, .ctx = ctx };
}

void print_int8(const void *x, void *ctx);
void print_int16(const void *x, void *ctx);
void print_int32(const void *x, void *ctx);
void print_int64(const void *x, void *ctx);

void print_uint8(const void *x, void *ctx);
void print_uint16(const void *x, void *ctx);
void print_uint32(const void *x, void *ctx);
void print_uint64(const void *x, void *ctx);

void print_float(const void *x, void *ctx);
void print_double(const void *x, void *ctx);
void print_long_double(const void *x, void *ctx);

void print_string(const void *x, void *ctx);

#endif //PRINT_H
