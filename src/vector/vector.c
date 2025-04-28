/*
 * ccol/vector.c
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "vector.h"
#include "vectorinternal.h"
#include "vector_iterator.h"
#include "comparator.h"
#include "ccol_status.h"
#include "ccol_constants.h"
#include "ccol_macros.h"

// Create / Initialize
ccol_status_t vector_init(vector_t *vec);
ccol_status_t vector_create(size_t capacity, size_t element_size, vector_t **vec_out);

// Insertion
ccol_status_t vector_append(vector_t *vec, void *data);
ccol_status_t vector_insert(vector_t *vec, size_t index, void *data);
ccol_status_t vector_insert_middle(vector_t *vec, size_t index, void *data);

// Fill
ccol_status_t vector_fill(vector_t *vec, void *value, size_t count);

// Removal
ccol_status_t vector_remove_value(vector_t *vec, comparator_t cmp, free_func_t free_data, void *ctx);
ccol_status_t vector_remove_at(vector_t *vec, size_t index);

ccol_status_t vector_pop(vector_t *vec, void **data_out);
ccol_status_t vector_pop_front(vector_t *vec, void **data_out);
ccol_status_t vector_pop_middle(vector_t *vec, void **data_out);
ccol_status_t vector_pop_back(vector_t *vec, void **data_out);

// Access
ccol_status_t vector_get(const vector_t *vec, size_t index, void** data_out);
ccol_status_t vector_get_index(const vector_t *vec, comparator_t cmp, size_t *index_out);

ccol_status_t vector_peek_front(const vector_t *vec, void **data_out);
ccol_status_t vector_peek_middle(const vector_t *vec, void **data_out);
ccol_status_t vector_peek_back(const vector_t *vec, void **data_out);

ccol_status_t vector_front(const vector_t *vec, void **data_out);
ccol_status_t vector_middle(const vector_t *vec, void **data_out);
ccol_status_t vector_back(const vector_t *vec, void **data_out);

// Attributes
size_t vector_size(const vector_t *vec);
size_t vector_capacity(const vector_t *vec);
bool vector_is_empty(const vector_t *vec);
bool vector_is_full(const vector_t *vec);
bool vector_contains(const vector_t *vec, void *data, comparator_t cmp, void *ctx);
ccol_status_t vector_at(const vector_t *vec, size_t index, void **data_out);

// Utilities
ccol_status_t vector_set(vector_t *vec, size_t index, void *value);
ccol_status_t vector_swap(vector_t *vec, size_t i, size_t j);
ccol_status_t vector_reserve(vector_t *vec, size_t new_capacity);
ccol_status_t vector_reserve_exact(vector_t *vec, size_t exact_capacity);
ccol_status_t vector_shrink_to_fit(vector_t *vec);
ccol_status_t vector_resize(vector_t *vec, size_t new_size, void *default_value);
ccol_status_t vector_assign(vector_t *vec, size_t count, void *value);

// Copy / Clone
ccol_status_t vector_clone(const vector_t *src, vector_t **vec_out, copy_func_t copy_data, void *ctx);
ccol_status_t vector_deep_clone(const vector_t *src, vector_t **vec_out, void *ctx);
ccol_status_t vector_copy(vector_t *dest, const vector_t *src, free_func_t free_data, copy_func_t copy_data, void *ctx);
ccol_status_t vector_deep_copy(vector_t *dest, const vector_t *src, free_func_t free_data, void *ctx);

// Cleanup
ccol_status_t vector_free(vector_t *vec, free_func_t free_data, void *ctx);
ccol_status_t vector_destroy(vector_t *vec, free_func_t free_data, void *ctx);
ccol_status_t vector_clear(vector_t *vec, free_func_t free_data, void *ctx);

// Print / Debug
ccol_status_t vector_print(const vector_t *vec, print_func_t print_data, void *ctx);
