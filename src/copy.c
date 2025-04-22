/*
 * ccol/copy.c
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "copy.h"

void *copy_int(const void *data, void *ctx) {
    int *copy = malloc(sizeof(int));
    if (!copy) return NULL;
    *copy = *(const int *)data;
    return copy;
}

void *copy_uint(const void *data, void *ctx);
void *copy_long(const void *data, void *ctx);
void *copy_long_long(const void *data, void *ctx);
void *copy_ulong(const void *data, void *ctx);
void *copy_ulong_long(const void *data, void *ctx);
void *copy_short(const void *data, void *ctx);
void *copy_ushort(const void *data, void *ctx);
void *copy_float(const void *data, void *ctx);
void *copy_double(const void *data, void *ctx);
void *copy_long_double(const void *data, void *ctx);
void *copy_char(const void *data, void *ctx);
void *copy_uchar(const void *data, void *ctx);
void *copy_str(const void *data, void *ctx);

void *copy_identity(const void *data, void *ctx) {
    return (void *)data;
}
