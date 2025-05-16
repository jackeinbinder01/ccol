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

typedef struct ccol_bitmap {
    uint8_t *data;
    size_t num_bits;

    bool is_initialized;
} ccol_bitmap_t;

// Constructors
void bitmap_init(ccol_bitmap_t *bitmap, size_t num_bits);
ccol_bitmap_t *bitmap_create(size_t num_bits);

// Set
void bitmap_set(ccol_bitmap_t *bitmap, size_t index, bool value);
bool bitmap_test(const ccol_bitmap_t *bitmap, size_t index);

// Set Operations
ccol_bitmap_t *bitmap_union(const ccol_bitmap_t *b1, const ccol_bitmap_t *b2);
ccol_bitmap_t *bitmap_intersection(const ccol_bitmap_t *b1, const ccol_bitmap_t *b2);
ccol_bitmap_t *bitmap_difference(const ccol_bitmap_t *b1, const ccol_bitmap_t *b2);
ccol_bitmap_t *bitmap_complement(const ccol_bitmap_t *bitmap);

void bitmap_union_inplace(ccol_bitmap_t *dest, const ccol_bitmap_t *src);
void bitmap_intersection_inplace(ccol_bitmap_t *dest, const ccol_bitmap_t *src);
void bitmap_difference_inplace(ccol_bitmap_t *dest, const ccol_bitmap_t *src);
void bitmap_complement_inplace(ccol_bitmap_t *bitmap);

void bitmap_toggle(ccol_bitmap_t *bitmap, size_t index);
void bitmap_flip_all(ccol_bitmap_t *bitmap);

// Logical
ccol_bitmap_t *bitmap_and(const ccol_bitmap_t *b1, const ccol_bitmap_t *b2);
ccol_bitmap_t *bitmap_or(const ccol_bitmap_t *b1, const ccol_bitmap_t *b2);
ccol_bitmap_t *bitmap_xor(const ccol_bitmap_t *b1, const ccol_bitmap_t *b2);

void bitmap_and_inplace(ccol_bitmap_t *dest, const ccol_bitmap_t *src);
void bitmap_or_inplace(ccol_bitmap_t *dest, const ccol_bitmap_t *src);
void bitmap_xor_inplace(ccol_bitmap_t *dest, const ccol_bitmap_t *src);

// Attributes
bool bitmap_equals(const ccol_bitmap_t *b1, const ccol_bitmap_t *b2);
size_t bitmap_num_bits(const ccol_bitmap_t *bitmap);
bool bitmap_is_empty(const ccol_bitmap_t *bitmap);
bool bitmap_is_full(const ccol_bitmap_t *bitmap);
bool bitmap_all(const ccol_bitmap_t *bitmap);
bool bitmap_any(const ccol_bitmap_t *bitmap);
bool bitmap_none(const ccol_bitmap_t *bitmap);


// Utilities
void bitmap_fill(ccol_bitmap_t *bitmap, bool value);
ccol_bitmap_t *bitmap_clone(const ccol_bitmap_t *bitmap);
void bitmap_copy(ccol_bitmap_t *dest, const ccol_bitmap_t *src);
size_t bitmap_find_first_set(const ccol_bitmap_t *bitmap);
size_t bitmap_find_first_clear(const ccol_bitmap_t *bitmap);

// Print
void bitmap_print(const ccol_bitmap_t *bitmap);

// Cleanup
void bitmap_free(ccol_bitmap_t *bitmap);
void bitmap_destroy(ccol_bitmap_t *bitmap);
void bitmap_clear(ccol_bitmap_t *bitmap);

// Iterator
iterator_t *bitmap_iterator_create(const ccol_bitmap_t *bitmap);

#define BITMAP_FOR(type, var, bitmap_ptr)                                           \
    for (iterator_t *_it = bitmap_iterator_create(bitmap_ptr); _it; _it = NULL)     \
        for (type *var = NULL;                                                      \
            _it->has_next(_it) &&                                                   \
            ((var = (type *)_it->next(_it)) || 1);)                                 \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // BITMAP_H
