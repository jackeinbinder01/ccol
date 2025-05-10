/*
 * ccol/copy.h
 *
 * Functions for copying pointers to primitives
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef COPY_H
#define COPY_H

#include "ccol_constants.h"

typedef struct {
    copy_func_t func;
    void *ctx;
} copy_t;

static inline copy_t copy_create(copy_func_t func, void *ctx) {
    return (copy_t){ .func = func, .ctx = ctx };
}

void *copy_int8(const void *data, void *ctx);
void *copy_int16(const void *data, void *ctx);
void *copy_int32(const void *data, void *ctx);
void *copy_int64(const void *data, void *ctx);

void *copy_uint8(const void *data, void *ctx);
void *copy_uint16(const void *data, void *ctx);
void *copy_uint32(const void *data, void *ctx);
void *copy_uint64(const void *data, void *ctx);

void *copy_str(const void *data, void *ctx); // Deep copy of null-terminated string
void *copy_identity(const void *data, void *ctx); // Shallow copy (returns passed object)

#endif //COPY_H
