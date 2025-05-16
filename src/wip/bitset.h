/*
 * ccol/bitset.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef BITSET_H
#define BITSET_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "iterator.h"

typedef struct bitset {
    uint64_t *array;
    size_t size;
    size_t capacity;

    bool is_initialized;
} bitset_t;

// Constructors
void bitset_init(bitset_t *bitset, size_t capacity);
bitset_t *bitset_create(size_t capacity);

// Set
void bitset_set(bitset_t *bitset, size_t index, bool value);
void bitset_set_all(bitset_t *bitset);

// Removal
void bitset_clear_bit(bitset_t *bitset, size_t index);

// Access
bool bitset_get(const bitset_t *bitset, size_t index);
bool bitset_test(const bitset_t *bitset, size_t index);

// Attributes
size_t bitset_size(const bitset_t *bitset);
size_t bitset_capacity(const bitset_t *bitset);
size_t bitset_popcount(const bitset_t *bitset);
bool bitset_is_empty(const bitset_t *bitset);
bool bitset_is_full(const bitset_t *bitset);
bool bitset_all(const bitset_t *bitset);
bool bitset_any(const bitset_t *bitset);
bool bitset_none(const bitset_t *bitset);

// Comparison
bool bitset_equals(const bitset_t *b1, const bitset_t *b2);
bool bitset_is_subset(const bitset_t *b1, const bitset_t *b2);
bool bitset_is_superset(const bitset_t *b1, const bitset_t *b2);

// Utilities
bitset_t *bitset_clone(const bitset_t *bitset);
void bitset_copy(bitset_t *dest, const bitset_t *src);
void bitset_swap(bitset_t *bitset, size_t i, size_t j);
void bitset_reserve(bitset_t *bitset, size_t new_capacity);
void bitset_shrink_to_fit(bitset_t *bitset);
void bitset_fill(bitset_t *bitset, bool value);

// Set Operations
bitset_t *bitset_union(const bitset_t *b1, const bitset_t *b2);
bitset_t *bitset_intersection(const bitset_t *b1, const bitset_t *b2);
bitset_t *bitset_difference(const bitset_t *b1, const bitset_t *b2);
bitset_t *bitset_complement(const bitset_t *bitset);

void bitset_union_inplace(bitset_t *dest, const bitset_t *src);
void bitset_intersection_inplace(bitset_t *dest, const bitset_t *src);
void bitset_difference_inplace(bitset_t *dest, const bitset_t *src);
void bitset_complement_inplace(bitset_t *bitset);
void bitset_toggle(bitset_t *bitset, size_t index);
void bitset_flip_all(bitset_t *bitset);

// Logical
bitset_t *bitset_and(const bitset_t *b1, const bitset_t *b2);
bitset_t *bitset_or(const bitset_t *b1, const bitset_t *b2);
bitset_t *bitset_xor(const bitset_t *b1, const bitset_t *b2);
void bitset_and_inplace(bitset_t *dest, const bitset_t *src);
void bitset_or_inplace(bitset_t *dest, const bitset_t *src);
void bitset_xor_inplace(bitset_t *dest, const bitset_t *src);

// Bit scanning
size_t bitset_find_first_set(const bitset_t *bitset);
size_t bitset_find_first_clear(const bitset_t *bitset);

// Print
void bitset_print(const bitset_t *bitset);

// Cleanup
void bitset_free(bitset_t *bitset);
void bitset_destroy(bitset_t *bitset);
void bitset_clear(bitset_t *bitset);

// Iterator
iterator_t *bitset_iterator_create(const bitset_t *bitset);

#define BITSET_FOR(type, var, bitset_ptr)                                           \
    for (iterator_t *_it = bitset_iterator_create(bitset_ptr); _it; _it = NULL)     \
        for (type *var = NULL;                                                      \
            _it->has_next(_it) &&                                                   \
            ((var = (type *)_it->next(_it)) || 1);)                                 \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // BITSET_H
