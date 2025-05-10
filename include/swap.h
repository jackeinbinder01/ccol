/*
 * ccol/swap.h
 *
 * Generic swap
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef SWAP_H
#define SWAP_H

#include <stdint.h>
#include <stddef.h>

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
ccol_status_t swap(void *x, void *y, size_t size);

#endif //SWAP_H
