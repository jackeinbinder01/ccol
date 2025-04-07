/*
 * ccol/copy.h
 *
 * Functions for copying pointers to primitives
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef COPY_H
#define COPY_H

typedef void *(*copy_data_t)(const void *);

void *copy_int(const void *data);
void *copy_uint(const void *data);
void *copy_long(const void *data);
void *copy_long_long(const void *data);
void *copy_ulong(const void *data);
void *copy_ulong_long(const void *data);
void *copy_short(const void *data);
void *copy_ushort(const void *data);
void *copy_float(const void *data);
void *copy_double(const void *data);
void *copy_long_double(const void *data);
void *copy_char(const void *data);
void *copy_uchar(const void *data);
void *copy_string(const void *data); // Deep copy of null-terminated string
void *copy_identity(const void *data); // Shallow copy (returns passed object)

#endif //COPY_H
