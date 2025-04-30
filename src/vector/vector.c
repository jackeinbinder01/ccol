/*
 * ccol/vector.c
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <cstddef>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "vector.h"
#include "vector_internal.h"
#include "vector_iterator.h"
#include "comparator.h"
#include "ccol_status.h"
#include "ccol_constants.h"
#include "ccol_macros.h"

// Create / Initialize
ccol_status_t vector_init(vector_t *vec, size_t capacity, size_t element_size) {
    if (!vec || element_size == 0) return CCOL_STATUS_INVALID_ARG;

    if (capacity > 0) {
        vec->data = calloc(capacity,element_size);
        if (!vec->data) return CCOL_STATUS_ALLOC;
    } else {
        vec->data = NULL;
    }
   
    vec->size = 0;
    vec->capacity = capacity;
    vec->element_size = element_size;
    vec->is_initialized = true;

    return CCOL_STATUS_OK;    
}

ccol_status_t vector_create(size_t capacity, size_t element_size, vector_t **vec_out) {
    if (!vec_out) return CCOL_STATUS_INVALID_ARG;

    vector_t *vec = calloc(1, sizeof(vector_t));
    if (!vec) return CCOL_STATUS_ALLOC;

    ccol_status_t status = vector_init(vec, capacity, element_size);
    if (status != CCOL_STATUS_OK) {
        free(vec);
        return status;
    }

    *vec_out = vec;
    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t vector_append(vector_t *vec, void *data) {
	CCOL_CHECK_INIT(vec);

    if (vec->size == vec->capacity) {
    	ccol_status_t status = vector_reserve(vec, vec->capacity == 0 ? 1: vec->capacity * 2);
        if (status != CCOL_STATUS_OK) return status;
    }

    void * target = (char *)vec->data + (vec->size * vec->element_size);
    memcpy(target, data, vec->element_size);
    vec->size++;

    return CCOL_STATUS_OK;
}

ccol_status_t vector_insert(vector_t *vec, size_t index, void *data) {
	CCOL_CHECK_INIT(vec);
    if (index > vec->size) return CCOL_STATUS_INVALID_ARG;

    if (vec->size == vec->capacity) {
    	ccol_status_t status = vector_reserve(vec, vec->capacity == 0 ? 1: vec->capacity * 2);
        if (status != CCOL_STATUS_OK) return status;
    }

    void *base = vec->data;
    size_t element_size = vec->element_size;

    // shift elements
    if (index < vec->size) {
    	void *src = (char *)base + index * element_size;
    	void *dest = (char *)base + (index + 1) * element_size;
    	size_t bytes = (vec->size - index) * element_size;
    	memmove(dest, src, bytes);
    }

    // insert
    void *target = (char *)base + index * element_size;
    if (data) memcpy(target, data, element_size);
    else memset(target, 0, element_size);

    vec->size++;

    return CCOL_STATUS_OK;
}

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

ccol_status_t vector_front(const vector_t *vec, void **data_out) {
	return vector_peek_front(vec, data_out);
}

ccol_status_t vector_middle(const vector_t *vec, void **data_out) {
	return vector_peek_middle(vec, data_out);
}

ccol_status_t vector_back(const vector_t *vec, void **data_out) {
	return vector_peek_back(vec, data_out);
}

// Attributes
size_t vector_size(const vector_t *vec) {
    if (!vec || !vec->is_initialized) return 0;
    return vec->size;
}

size_t vector_capacity(const vector_t *vec) {
    if (!vec || !vec->is_initialized) return 0;
    return vec->capacity;
}

bool vector_is_empty(const vector_t *vec) {
    if (!vec || !vec->is_initialized) return true;
    return vec->size == 0;
}

bool vector_is_full(const vector_t *vec) {
    if (!vec || !vec->is_initialized) return true;
    return vec->capacity == vec->size;
}

bool vector_contains(const vector_t *vec, void *data, comparator_t cmp, void *ctx);
ccol_status_t vector_at(const vector_t *vec, size_t index, void **data_out);

// Utilities
ccol_status_t vector_set(vector_t *vec, size_t index, void *value);
ccol_status_t vector_swap(vector_t *vec, size_t i, size_t j);
ccol_status_t vector_reserve(vector_t *vec, size_t new_capacity) {
	CCOL_CHECK_INIT(vec);
    if (new_capacity <= vec->capacity) return CCOL_STATUS_OK;

    void *new_data = calloc(new_capacity, vec->element_size);
    if (!new_data) return CCOL_STATUS_ALLOC;

    if (vec->data && vec->size > 0) {
    	memcpy(new_data, vec->data, vec->size * vec->element_size);
    }

    free(vec->data);
    vec->data = new_data;
    vec->capacity = new_capacity;

    return CCOL_STATUS_OK;
}

ccol_status_t vector_reserve_exact(vector_t *vec, size_t exact_capacity) {
	CCOL_CHECK_INIT(vec);
    if (exact_capacity < vec->capacity) return CCOL_STATUS_INVALID_ARG;
    if (exact_capacity == vec->capacity) return CCOL_STATUS_OK;


	void *new_data = calloc(exact_capacity, vec->element_size);
    if (!new_data) return CCOL_STATUS_ALLOC;

    if (vec->data && vec->size > 0) {
    	memcpy(new_data, vec->data, vec->size * vec->element_size);
    }

    free(vec->data);
    vec->data = new_data;
    vec->capacity = exact_capacity;

    return CCOL_STATUS_OK;
}

ccol_status_t vector_shrink_to_fit(vector_t *vec) {
	CCOL_CHECK_INIT(vec);
    if (vec->size == vec->capacity) return CCOL_STATUS_OK;

    if (vec->size == 0) {
    	free(vec->data);
        vec->data = NULL;
        vec->capacity = 0;
        return CCOL_STATUS_OK;
    }

    void *new_data = realloc(vec->data, vec->size * vec->element_size);
    if (!new_data) return CCOL_STATUS_ALLOC;

    vec->data = new_data;
    vec->capacity = vec->size;
    return CCOL_STATUS_OK;
}

ccol_status_t vector_resize(vector_t *vec, size_t new_size, void *default_value);
ccol_status_t vector_assign(vector_t *vec, size_t count, void *value);

// Copy / Clone
ccol_status_t vector_clone(const vector_t *src, vector_t **vec_out, copy_func_t copy_data, void *ctx);

ccol_status_t vector_deep_clone(const vector_t *src, vector_t **vec_out, void *ctx) {
    CCOL_CHECK_INIT(src);
    if (!*vec_out) return CCOL_STATUS_INVALID_ARG;

    return vector_clone(src, vec_out, COPY DEFAULT, ctx);
}

ccol_status_t vector_copy(vector_t *dest, const vector_t *src, free_func_t free_data, copy_func_t copy_data, void *ctx);

ccol_status_t vector_deep_copy(vector_t *dest, const vector_t *src, free_func_t free_data, void *ctx) {
    return vector_copy(dest, src, free_data, COPY_DEFAULT, ctx);
}

// Cleanup
ccol_status_t vector_clear(vector_t *vec, free_func_t free_data, void *ctx) {
    CCOL_CHECK_INIT(vec);

    if (free_data) {
        for (size_t i = 0; i < vec->size; i++) {
            void *element = (char *)vec->data + (i * vec->element_size);
            free_data(element, ctx);
        }
    }

    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    vec->element_size = 0;

    return CCOL_STATUS_OK;
}

ccol_status_t vector_destroy(vector_t *vec, free_func_t free_data, void *ctx) {
    CCOL_CHECK_INIT(vec);

    ccol_status_t status = vector_clear(vec, free_data, ctx);
    if (status != CCOL_STATUS_OK) return status;

    vector_uninit(vec);

    return CCOL_STATUS_OK;
}

ccol_status_t vector_free(vector_t **vec_ptr, free_func_t free_data, void *ctx) {
    if (!vec_ptr || !*vec_ptr || !(*vec_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = vector_destroy(*vec_ptr, free_data, ctx);
    free(*vec_ptr);
    *vec_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t vector_print(const vector_t *vec, print_func_t print_data, void *ctx) {
    CCOL_CHECK_INIT(vec);
    if (!print_data) return CCOL_STATUS_INVALID_ARG;
    if (vec->size == 0) {
        printf("[]\n");
        return CCOL_STATUS_OK;
    }

    printf("[");
    for (size_t i = 0; i < vec->size; i++) {
        void *element = (char *)vec->data + (i * vec->element_size);
        print_data(element, ctx);
        if (i < vec->size - 1) printf(", ");
    }
    printf("]\n");

    return CCOL_STATUS_OK;
}
