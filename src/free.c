/*
 * ccol/free.c
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>

#include "free.h"

void free_default(void *ptr, void *ctx) {
    (void)ctx;
    free(ptr);
}

void free_str(void *ptr, void *ctx) {
    (void)ctx;
    free(ptr);
}

void free_noop(void *ptr, void *ctx) {
    (void)ctx;
    (void)ptr;
}
