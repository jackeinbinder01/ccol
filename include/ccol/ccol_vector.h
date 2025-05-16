/*
 * ccol/ccol_vector.h
 *
 * Dynamic array (vector) API.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_VECTOR_H
#define CCOL_VECTOR_H

#include <stddef.h>
#include <stdbool.h>

#include "ccol_constants.h"
#include "ccol_status.h"
#include "ccol_iterator.h"
#include "ccol_copy.h"
#include "ccol_free.h"
#include "ccol_print.h"
#include "ccol_comparator.h"

typedef struct ccol_vector {
    void *data;

    size_t size;
    size_t capacity;
    size_t element_size;

    ccol_copy_t copier;
    ccol_free_t freer;
    ccol_print_t printer;
    ccol_comparator_t comparator;

    bool is_initialized;
} ccol_vector_t;

// Create / Initialize
ccol_status_t ccol_vector_init(
    ccol_vector_t *vec,
    size_t capacity,
    size_t element_size,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

ccol_status_t ccol_vector_create(
    ccol_vector_t **vec_out,
    size_t capacity,
    size_t element_size,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

// Insertion
ccol_status_t ccol_vector_append(ccol_vector_t *vec, void *data);
ccol_status_t ccol_vector_insert(ccol_vector_t *vec, size_t index, void *data);
ccol_status_t ccol_vector_insert_middle(ccol_vector_t *vec, size_t index, void *data);

// Fill / Assign
ccol_status_t ccol_vector_fill(ccol_vector_t *vec, size_t count, void *value);
ccol_status_t ccol_vector_assign(ccol_vector_t *vec, size_t count, void *value);

// Removal
ccol_status_t ccol_vector_remove_value(ccol_vector_t *vec, void *value);
ccol_status_t ccol_vector_remove_at(ccol_vector_t *vec, size_t index);

ccol_status_t ccol_vector_pop(ccol_vector_t *vec, void **data_out);
ccol_status_t ccol_vector_pop_front(ccol_vector_t *vec, void **data_out);
ccol_status_t ccol_vector_pop_middle(ccol_vector_t *vec, void **data_out);
ccol_status_t ccol_vector_pop_back(ccol_vector_t *vec, void **data_out);

// Access
ccol_status_t ccol_vector_get(const ccol_vector_t *vec, size_t index, void** data_out);
ccol_status_t ccol_vector_get_index(const ccol_vector_t *vec, void *value, size_t *index_out);

ccol_status_t ccol_vector_peek_at(const ccol_vector_t *vec, size_t index, void **data_out);
ccol_status_t ccol_vector_peek_front(const ccol_vector_t *vec, void **data_out);
ccol_status_t ccol_vector_peek_middle(const ccol_vector_t *vec, void **data_out);
ccol_status_t ccol_vector_peek_back(const ccol_vector_t *vec, void **data_out);

ccol_status_t ccol_vector_front(const ccol_vector_t *vec, void **data_out);
ccol_status_t ccol_vector_middle(const ccol_vector_t *vec, void **data_out);
ccol_status_t ccol_vector_back(const ccol_vector_t *vec, void **data_out);

// Attributes
size_t ccol_vector_size(const ccol_vector_t *vec);
size_t ccol_vector_capacity(const ccol_vector_t *vec);
bool ccol_vector_is_empty(const ccol_vector_t *vec);
bool ccol_vector_is_full(const ccol_vector_t *vec);
bool ccol_vector_contains(const ccol_vector_t *vec, void *data);
ccol_status_t ccol_vector_at(const ccol_vector_t *vec, size_t index, void **data_out);

// Utilities
ccol_status_t ccol_vector_set(ccol_vector_t *vec, size_t index, void *value);
ccol_status_t ccol_vector_swap(ccol_vector_t *vec, size_t i, size_t j);
ccol_status_t ccol_vector_reserve(ccol_vector_t *vec, size_t new_capacity);
ccol_status_t ccol_vector_reserve_exact(ccol_vector_t *vec, size_t exact_capacity);
ccol_status_t ccol_vector_shrink_to_fit(ccol_vector_t *vec);
ccol_status_t ccol_vector_resize(ccol_vector_t *vec, size_t new_size, void *default_value);

// Copy / Clone
ccol_status_t ccol_vector_clone(const ccol_vector_t *src, ccol_vector_t **vec_out);
ccol_status_t ccol_vector_deep_clone(const ccol_vector_t *src, ccol_vector_t **vec_out);
ccol_status_t ccol_vector_shallow_clone(const ccol_vector_t *src, ccol_vector_t **vec_out);

ccol_status_t ccol_vector_copy(ccol_vector_t *dest, const ccol_vector_t *src);
ccol_status_t ccol_vector_deep_copy(ccol_vector_t *dest, const ccol_vector_t *src);
ccol_status_t ccol_vector_shallow_copy(ccol_vector_t *dest, const ccol_vector_t *src);

// Cleanup
ccol_status_t ccol_vector_clear(ccol_vector_t *vec);
ccol_status_t ccol_vector_destroy(ccol_vector_t *vec);
ccol_status_t ccol_vector_free(ccol_vector_t **vec_ptr);

// Print / Debug
ccol_status_t ccol_vector_print(const ccol_vector_t *vec);

#endif  // CCOL_VECTOR_H
