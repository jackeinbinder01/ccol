/*
 * ccol/free.h
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef FREE_H
#define FREE_H

#include "ccol_constants.h"

typedef struct {
    free_func_t func;
    void *ctx;
} free_t;

static inline free_t free_create(free_func_t func, void *ctx) {
    return (free_t){ .func = func, .ctx = ctx };
}

void free_default(void *ptr, void *ctx);
void free_str(void *ptr, void *ctx);
void free_noop(void *ptr, void *ctx);

#endif //FREE_H
