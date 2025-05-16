/*
 * ccol/src/core/ccol_free.c
 *
 * Function wrapper for dynamic memory cleanup.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>

#include "ccol/ccol_free.h"

void ccol_free_default(void *ptr, void *ctx) {
    (void)ctx;
    free(ptr);
}

void ccol_free_str(void *ptr, void *ctx) {
    (void)ctx;
    free(ptr);
}

void ccol_free_noop(void *ptr, void *ctx) {
    (void)ctx;
    (void)ptr;
}
