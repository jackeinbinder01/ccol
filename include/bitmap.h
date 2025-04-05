/*
 * ccol/bitmap.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "iterator.h"

typedef struct bitmap_t {
    uint8_t *data;
    size_t num_bits;

    bool is_initialized;
} bitmap_t;

// Constructors
void bitmap_init(bitmap_t *bitmap, size_t num_bits);
bitmap_t *bitmap_create(size_t num_bits);

// Set
void bitmap_set(bitmap_t *bitmap, size_t index, bool value);
bool bitmap_test(const bitmap_t *bitmap, size_t index);

// Set Operations
bitmap_t *bitmap_union(const bitmap_t *b1, const bitmap_t *b2);
bitmap_t *bitmap_intersection(const bitmap_t *b1, const bitmap_t *b2);
bitmap_t *bitmap_difference(const bitmap_t *b1, const bitmap_t *b2);
bitmap_t *bitmap_complement(const bitmap_t *bitmap);

void bitmap_union_inplace(bitmap_t *dest, const bitmap_t *src);
void bitmap_intersection_inplace(bitmap_t *dest, const bitmap_t *src);
void bitmap_difference_inplace(bitmap_t *dest, const bitmap_t *src);
void bitmap_complement_inplace(bitmap_t *bitmap);

void bitmap_toggle(bitmap_t *bitmap, size_t index);
void bitmap_flip_all(bitmap_t *bitmap);

// Logical
bitmap_t *bitmap_and(const bitmap_t *b1, const bitmap_t *b2);
bitmap_t *bitmap_or(const bitmap_t *b1, const bitmap_t *b2);
bitmap_t *bitmap_xor(const bitmap_t *b1, const bitmap_t *b2);

void bitmap_and_inplace(bitmap_t *dest, const bitmap_t *src);
void bitmap_or_inplace(bitmap_t *dest, const bitmap_t *src);
void bitmap_xor_inplace(bitmap_t *dest, const bitmap_t *src);

// Attributes
bool bitmap_equals(const bitmap_t *b1, const bitmap_t *b2);
size_t bitmap_num_bits(const bitmap_t *bitmap);
bool bitmap_is_empty(const bitmap_t *bitmap);
bool bitmap_is_full(const bitmap_t *bitmap);
bool bitmap_all(const bitmap_t *bitmap);
bool bitmap_any(const bitmap_t *bitmap);
bool bitmap_none(const bitmap_t *bitmap);


// Utilities
void bitmap_fill(bitmap_t *bitmap, bool value);
bitmap_t *bitmap_clone(const bitmap_t *bitmap);
void bitmap_copy(bitmap_t *dest, const bitmap_t *src);
size_t bitmap_find_first_set(const bitmap_t *bitmap);
size_t bitmap_find_first_clear(const bitmap_t *bitmap);

// Print
void bitmap_print(const bitmap_t *bitmap);

// Cleanup
void bitmap_free(bitmap_t *bitmap);
void bitmap_destroy(bitmap_t *bitmap);
void bitmap_clear(bitmap_t *bitmap);

// Iterator
iterator_t *bitmap_iterator_create(const bitmap_t *bitmap);

#define BITMAP_FOR(type, var, bitmap_ptr)                                           \
    for (iterator_t *_it = bitmap_iterator_create(bitmap_ptr); _it; _it = NULL)     \
        for (type *var = NULL;                                                      \
            _it->has_next(_it) &&                                                   \
            ((var = (type *)_it->next(_it)) || 1);)                                 \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // BITMAP_H
