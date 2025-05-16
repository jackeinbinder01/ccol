/*
 * ccol/src/core/cool_copy.c
 *
 * Function wrapper for deep and shallow copying.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ccol/ccol_copy.h"

void *ccol_copy_int8(const void *data, void *ctx);
void *ccol_copy_int16(const void *data, void *ctx);
void *ccol_copy_int32(const void *data, void *ctx);
void *ccol_copy_int64(const void *data, void *ctx);

void *ccol_copy_uint8(const void *data, void *ctx);
void *ccol_copy_uint16(const void *data, void *ctx);
void *ccol_copy_uint32(const void *data, void *ctx);
void *ccol_copy_uint64(const void *data, void *ctx);

void *ccol_copy_str(const void *data, void *ctx); // Deep copy of null-terminated string

void *ccol_copy_identity(const void *data, void *ctx) {
    (void)ctx;
    return (void *)data;
}
