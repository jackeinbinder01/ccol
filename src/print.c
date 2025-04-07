/*
 * ccol/print.c
 *
 * Print implementations
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdio.h>

void print_int(const void *x) {
    printf("%d", *(const int *)x);
}

void print_uint(const void *x);
void print_long(const void *x);
void print_long_long(const void *x);
void print_ulong(const void *x);
void print_ulong_long(const void *x);
void print_short(const void *x);
void print_ushort(const void *x);
void print_float(const void *x);
void print_double(const void *x);
void print_long_double(const void *x);
void print_char(const void *x);
void print_uchar(const void *x);
void print_string(const void *x);
