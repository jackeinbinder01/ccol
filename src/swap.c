/*
 * ccol/swap.c
 *
 * Swap implementations
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "swap.h"
#include "ccol_status.h"

ccol_status_t swap_int8(int8_t *x, int8_t *y);
ccol_status_t swap_int16(int16_t *x, int16_t *y);
ccol_status_t swap_int32(int32_t *x, int32_t *y);
ccol_status_t swap_int64(int64_t *x, int64_t *y);

ccol_status_t swap_uint8(uint8_t *x, uint8_t *y);
ccol_status_t swap_uint16(uint16_t *x, uint16_t *y);
ccol_status_t swap_uint32(uint32_t *x, uint32_t *y);
ccol_status_t swap_uint64(uint64_t *x, uint64_t *y);

ccol_status_t swap_string(char **s1, char **s2);

ccol_status_t swap(void *x, void *y, size_t size) {
    if (!x || !y || size == 0) return CCOL_STATUS_INVALID_ARG;

    uint8_t *tmp = malloc(size);
    if (!tmp) return CCOL_STATUS_ALLOC;

    memcpy(tmp, x, size);
    memcpy(x, y, size);
    memcpy(y, tmp, size);

    free(tmp);
    return CCOL_STATUS_OK;
}
