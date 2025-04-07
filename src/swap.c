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

ccol_status_t swap_int(int *x, int *y);
ccol_status_t swap_uint(unsigned int *x, unsigned int *y);
ccol_status_t swap_long(long *x, long *y);
ccol_status_t swap_long_long(long long *x, long long *y);
ccol_status_t swap_ulong(unsigned long *x, unsigned long *y);
ccol_status_t swap_ulong_long(unsigned long long *x, unsigned long long *y);
ccol_status_t swap_short(short int *x, short int *y);
ccol_status_t swap_ushort(unsigned short int *x, unsigned short int *y);
ccol_status_t swap_float(float *x, float *y);
ccol_status_t swap_double(double *x, double *y);
ccol_status_t swap_long_double(long double *x, long double *y);
ccol_status_t swap_char(char *x, char *y);
ccol_status_t swap_uchar(unsigned char *x, unsigned char *y);
ccol_status_t swap_string(char **s1, char **s2);

ccol_status_t swap(void *x, void *y, size_t size) {
    if (!x || !y || size == 0) return CCOL_STATUS_INVALID_ARG;

    void *tmp = malloc(size);
    if (!tmp) return CCOL_STATUS_ALLOC;

    memcpy(tmp, x, size);
    memcpy(x, y, size);
    memcpy(y, tmp, size);

    free(tmp);
    return CCOL_STATUS_OK;
}
