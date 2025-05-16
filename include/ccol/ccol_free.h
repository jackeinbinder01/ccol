/*
 * ccol/ccol_free.h
 *
 * Function wrapper for dynamic memory cleanup.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_FREE_H
#define CCOL_FREE_H

#include "ccol_constants.h"

typedef struct ccol_free {
    ccol_free_func_t func;
    void *ctx;
} ccol_free_t;

static inline ccol_free_t ccol_free_create(ccol_free_func_t func, void *ctx) {
    return (ccol_free_t){ .func = func, .ctx = ctx };
}

void ccol_free_default(void *ptr, void *ctx);
void ccol_free_str(void *ptr, void *ctx);
void ccol_free_noop(void *ptr, void *ctx);

#endif  // CCOL_FREE_H
