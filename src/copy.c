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

void *copy_int8(const void *data, void *ctx);
void *copy_int16(const void *data, void *ctx);
void *copy_int32(const void *data, void *ctx);
void *copy_int64(const void *data, void *ctx);

void *copy_uint8(const void *data, void *ctx);
void *copy_uint16(const void *data, void *ctx);
void *copy_uint32(const void *data, void *ctx);
void *copy_uint64(const void *data, void *ctx);

void *copy_str(const void *data, void *ctx); // Deep copy of null-terminated string

void *copy_identity(const void *data, void *ctx) {
    return (void *)data;
}
