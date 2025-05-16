/*
 * ccol/src/core/cool_print.c
 *
 * Function wrappers for printing values with printf-style handlers.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "ccol/ccol_print.h"

void ccol_print_int8(const void *x, void *ctx) {
    (void)ctx;
    printf("%" PRId8, *(const int8_t *)x);
}

void ccol_print_int16(const void *x, void *ctx) {
    (void)ctx;
    printf("%" PRId16, *(const int16_t *)x);
}

void ccol_print_int32(const void *x, void *ctx) {
    (void)ctx;
    printf("%" PRId32, *(const int32_t *)x);
}

void ccol_print_int64(const void *x, void *ctx) {
    (void)ctx;
    printf("%" PRId64, *(const int64_t *)x);
}

void ccol_print_uint8(const void *x, void *ctx) {
    (void)ctx;
    printf("%" PRIu8, *(const uint8_t *)x);
}

void ccol_print_uint16(const void *x, void *ctx) {
    (void)ctx;
    printf("%" PRIu16, *(const uint16_t *)x);
}

void ccol_print_uint32(const void *x, void *ctx) {
    (void)ctx;
    printf("%" PRIu32, *(const uint32_t *)x);
}

void ccol_print_uint64(const void *x, void *ctx) {
    (void)ctx;
    printf("%" PRIu64, *(const uint64_t *)x);
}

void ccol_print_float(const void *x, void *ctx) {
    (void)ctx;
    printf("%f", *(const float *)x);
}

void ccol_print_double(const void *x, void *ctx) {
    (void)ctx;
    printf("%lf", *(const double *)x);
}

void ccol_print_long_double(const void *x, void *ctx) {
    (void)ctx;
    printf("%lf", (double)*(const long double *)x);
}

void ccol_print_string(const void *x, void *ctx) {
    (void)ctx;
    printf("%s", *(const char **)x);
}
