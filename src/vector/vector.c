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
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "vector.h"
#include "vector_internal.h"
#include "vector_iterator.h"
#include "comparator.h"
#include "ccol_status.h"
#include "ccol_constants.h"
#include "ccol_macros.h"

// Create / Initialize
ccol_status_t vector_init(
    vector_t *vec,
    size_t capacity,
    size_t element_size,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
) {
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
    vec->copier = copier;
    vec->freer = freer;
    vec->printer = printer;
    vec->comparator = comparator;

    vec->is_initialized = true;

    return CCOL_STATUS_OK;    
}

ccol_status_t vector_create(
    vector_t **vec_out,
    size_t capacity,
    size_t element_size,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
) {
    if (!vec_out) return CCOL_STATUS_INVALID_ARG;

    vector_t *vec = calloc(1, sizeof(vector_t));
    if (!vec) return CCOL_STATUS_ALLOC;

    ccol_status_t status = vector_init(vec, capacity, element_size, copier, freer, printer, comparator);
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

ccol_status_t vector_insert_middle(vector_t *vec, void *data) {
	CCOL_CHECK_INIT(vec);
    size_t middle = vec->size / 2;
    return vector_insert(vec, middle, data);
}

// Fill
ccol_status_t vector_fill(vector_t *vec, size_t count, void *value) {
	CCOL_CHECK_INIT(vec);
    if (count == 0) return CCOL_STATUS_OK;

    ccol_status_t status;
    if (count > vec->size) {
    	status = vector_reserve(vec, count);
        if (status != CCOL_STATUS_OK) return status;
    }

    for (size_t i = 0; i < count; i++) {
    	void *element = (char *)vec->data + (i * vec->element_size);
        if (vec->freer.func && i < vec->size) vec->freer.func(element, vec->freer.ctx);
        memcpy(element, value, vec->element_size);
    }

	if (count > vec->size) vec->size = count;

    return CCOL_STATUS_OK;
}

ccol_status_t vector_assign(vector_t *vec, size_t count, void *value) {
	ccol_status_t status = vector_clear(vec);
    if (status != CCOL_STATUS_OK) return status;
    if (count == 0) return CCOL_STATUS_OK;

    for (size_t i = 0; i < count; i++) {
    	status = vector_append(vec, value);
        if (status != CCOL_STATUS_OK) return status;
    }

    return CCOL_STATUS_OK;
}

// Removal
ccol_status_t vector_remove_value(vector_t *vec, void *value) {
	CCOL_CHECK_INIT(vec);

    size_t index = 0;
    ccol_status_t status = vector_get_index(vec, value, &index);
    if (status != CCOL_STATUS_OK) return status;

    return vector_remove_at(vec, index);
}

ccol_status_t vector_remove_at(vector_t *vec, size_t index) {
	CCOL_CHECK_INIT(vec);
    if (index >= vec->size) return CCOL_STATUS_OUT_OF_BOUNDS;

	void *element = (char *)vec->data + (index * vec->element_size);
    if (vec->freer.func) vec->freer.func(element, vec->freer.ctx);

    // shift elements
    size_t remaining = vec->size - index - 1;
    if (remaining > 0) {
    	void *src = (char *)vec->data + ((index + 1) * vec->element_size);
        memmove(element, src, remaining * vec->element_size);
    }

    vec->size--;
    return CCOL_STATUS_OK;
}

ccol_status_t vector_pop(vector_t *vec, void **data_out) {
	return vector_pop_back(vec, data_out);
}

ccol_status_t vector_pop_front(vector_t *vec, void **data_out) {
	ccol_status_t status = vector_peek_front(vec, data_out);
    if (status != CCOL_STATUS_OK) return status;
    return vector_remove_at(vec, 0);
}

ccol_status_t vector_pop_middle(vector_t *vec, void **data_out) {
	size_t middle = vec->size / 2;
	ccol_status_t status = vector_peek_middle(vec, data_out);
    if (status != CCOL_STATUS_OK) return status;
    return vector_remove_at(vec, middle);
}

ccol_status_t vector_pop_back(vector_t *vec, void **data_out) {
  	size_t back = vec->size - 1;
	ccol_status_t status = vector_peek_back(vec, data_out);
    if (status != CCOL_STATUS_OK) return status;
    return vector_remove_at(vec, back);
}

// Access
ccol_status_t vector_get(const vector_t *vec, size_t index, void** data_out) {
	CCOL_CHECK_INIT(vec);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (vec->size == 0) return CCOL_STATUS_EMPTY;
    if (index >= vec->size) return CCOL_STATUS_OUT_OF_BOUNDS;

    void *element = (char *)vec->data + (index * vec->element_size);

    *data_out = element;

    return CCOL_STATUS_OK;
}

ccol_status_t vector_at(const vector_t *vec, size_t index, void **data_out) {
	return vector_get(vec, index, data_out);
}

ccol_status_t vector_get_index(const vector_t *vec, void *value, size_t *index_out) {
  	CCOL_CHECK_INIT(vec);
    if (!index_out) return CCOL_STATUS_INVALID_ARG;
    if (!vec->comparator.func) return CCOL_STATUS_COMPARATOR_FUNC;
    if (vec->size == 0) return CCOL_STATUS_EMPTY;

    for (size_t i = 0; i < vec->size; i++) {
    	void *element = (char *)vec->data + (i * vec->element_size);
        if (vec->comparator.func(element, value, vec->comparator.ctx) == 0) {
        	*index_out = i;
            return CCOL_STATUS_OK;
        }
    }

    return CCOL_STATUS_NOT_FOUND;
}

ccol_status_t vector_peek_at(const vector_t *vec, size_t index, void **data_out) {
	CCOL_CHECK_INIT(vec);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (vec->size == 0) return CCOL_STATUS_EMPTY;
    if (index >= vec->size) return CCOL_STATUS_OUT_OF_BOUNDS;

    void *element = (char *)vec->data + (index * vec->element_size);

    void *copy = malloc(vec->element_size);
    if (!copy) return CCOL_STATUS_ALLOC;
    memcpy(copy, element, vec->element_size);
    *data_out = copy;

    return CCOL_STATUS_OK;
}

ccol_status_t vector_peek_front(const vector_t *vec, void **data_out) {
	return vector_peek_at(vec, 0, data_out);
}

ccol_status_t vector_peek_middle(const vector_t *vec, void **data_out) {
	size_t middle = vec->size / 2;
	return vector_peek_at(vec, middle, data_out);
}

ccol_status_t vector_peek_back(const vector_t *vec, void **data_out) {
  	size_t back = vec->size - 1;
	return vector_peek_at(vec, back, data_out);
}

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

bool vector_contains(const vector_t *vec, void *value) {
	CCOL_CHECK_INIT(vec);
    if (!vec->comparator.func) return false;

	for (size_t i = 0; i < vec->size; i++) {
    	void *element = (char *)vec->data + (i * vec->element_size);
        if (vec->comparator.func(element, value, vec->comparator.ctx) == 0) return true;
    }

    return false;
}

// Utilities
ccol_status_t vector_set(vector_t *vec, size_t index, void *value) {
	CCOL_CHECK_INIT(vec);
    if (index >= vec->size) return CCOL_STATUS_OUT_OF_BOUNDS;

    void *element = (char *)vec->data + (index * vec->element_size);
    if (vec->freer.func) vec->freer.func(element, vec->freer.ctx);
    memcpy(element, value, vec->element_size);

    return CCOL_STATUS_OK;
}

ccol_status_t vector_swap(vector_t *vec, size_t i, size_t j) {
	CCOL_CHECK_INIT(vec);
    if (i >= vec->size || j >= vec->size) return CCOL_STATUS_OUT_OF_BOUNDS;

    void *element_i = (char *)vec->data + (i * vec->element_size);
    void *element_j = (char *)vec->data + (j * vec->element_size);

    return swap(element_i, element_j, vec->element_size);
}

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

ccol_status_t vector_ensure_capacity(vector_t *vec, size_t min_capacity) {
    CCOL_CHECK_INIT(vec);
    if (vec->capacity >= min_capacity) return CCOL_STATUS_OK;

    size_t new_capacity = vec->capacity == 0 ? 1 : vec->capacity;
    while (new_capacity < min_capacity) new_capacity *= 2; 
    if (new_capacity > SIZE_MAX / vec->element_size) return CCOL_STATUS_OVERFLOW;

    void *new_data = realloc(vec->data, new_capacity * vec->element_size);
    if (!new_data) return CCOL_STATUS_ALLOC;
    
    vec->data = new_data;
    vec->capacity = new_capacity;

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

ccol_status_t vector_resize(vector_t *vec, size_t new_size, void *default_value) {
    CCOL_CHECK_INIT(vec);
    if (new_size == vec->size) return CCOL_STATUS_OK;

    ccol_status_t status;
    if (new_size > vec->size) {
        if (new_size > vec->capacity) {
            status = vector_ensure_capacity(vec, new_size);
            if (status != CCOL_STATUS_OK) return status;
        }

        for (size_t i = vec->size; i < new_size; i++) {
            status = vector_append(vec, default_value);
            if (status != CCOL_STATUS_OK) return status;
        }
    } else {
        for (ssize_t i = (ssize_t)vec->size - 1; i >= (ssize_t)new_size; i--) {
            status = vector_remove_at(vec, i);
            if (status != CCOL_STATUS_OK) return status;
        }
    }

    return CCOL_STATUS_OK;
}

// Copy / Clone
ccol_status_t vector_clone(const vector_t *src, vector_t **vec_out) {
	CCOL_CHECK_INIT(src);
    if (!vec_out) return CCOL_STATUS_INVALID_ARG;
    if (!src->copier.func) return CCOL_STATUS_COPY_FUNC;

    *vec_out = NULL;

    ccol_status_t status = vector_create(
        vec_out,
        src->capacity,
        src->element_size,
        src->copier,
        src->freer,
        src->printer,
        src->comparator
    );
    if (status != CCOL_STATUS_OK) return status;

    for (size_t i = 0; i < src->size; i++) {
     	void *element = (char *)src->data + (i * src->element_size);

        void *element_copy = src->copier.func(element, src->copier.ctx);
    	if (!element_copy && element != NULL) {
        	vector_destroy(*vec_out);
        	*vec_out = NULL;
        	return CCOL_STATUS_COPY;
    	}

        status = vector_append(*vec_out, element_copy);
        	if (status != CCOL_STATUS_OK) {
            	if (src->freer.func && element_copy) src->freer.func(element_copy, src->freer.ctx);
    			vector_destroy(*vec_out);
        		*vec_out = NULL;
        	return status;
    	}
    }

    return CCOL_STATUS_OK;
}

ccol_status_t vector_deep_clone(const vector_t *src, vector_t **vec_out) {
    CCOL_CHECK_INIT(src);
    if (!*vec_out) return CCOL_STATUS_INVALID_ARG;

    return vector_clone(src, vec_out);
}

ccol_status_t vector_copy(vector_t *dest, const vector_t *src) {
    CCOL_CHECK_INIT(dest);
    CCOL_CHECK_INIT(src);
    if (!src->copier.func) return CCOL_STATUS_COPY_FUNC;

    ccol_status_t status = vector_clear(dest);
    if (status != CCOL_STATUS_OK) return status;

    for (size_t i = 0; i < src->size; i++) {
     	void *element = (char *)src->data + (i * src->element_size);

        void *element_copy = src->copier.func(element, src->copier.ctx);
    	if (!element_copy && element != NULL) {
        	status = vector_clear(dest);
        	return status != CCOL_STATUS_OK ? status: CCOL_STATUS_COPY;
    	}

        status = vector_append(dest, element_copy);
        if (status != CCOL_STATUS_OK) {
            if (src->freer.func && element_copy) src->freer.func(element_copy, src->freer.ctx);
            ccol_status_t clear_status = vector_clear(dest);
            return clear_status != CCOL_STATUS_OK ? clear_status: status;
    	}
    }

    return CCOL_STATUS_OK;
}

ccol_status_t vector_deep_copy(vector_t *dest, const vector_t *src) {
    return vector_copy(dest, src);
}

// Cleanup
ccol_status_t vector_clear(vector_t *vec) {
    CCOL_CHECK_INIT(vec);

    if (vec->freer.func) {
        for (size_t i = 0; i < vec->size; i++) {
            void *element = (char *)vec->data + (i * vec->element_size);
            vec->freer.func(element, vec->freer.ctx);
        }
    }

    free(vec->data);
    vec->data = NULL;
    vec->size = vec->capacity = vec->element_size =0;

    return CCOL_STATUS_OK;
}

ccol_status_t vector_destroy(vector_t *vec) {
    CCOL_CHECK_INIT(vec);

    ccol_status_t status = vector_clear(vec);
    if (status != CCOL_STATUS_OK) return status;

    vector_uninit(vec);

    return CCOL_STATUS_OK;
}

ccol_status_t vector_free(vector_t **vec_ptr) {
    if (!vec_ptr || !*vec_ptr || !(*vec_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = vector_destroy(*vec_ptr);
    free(*vec_ptr);
    *vec_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t vector_print(const vector_t *vec) {
    CCOL_CHECK_INIT(vec);
    if (!vec->printer.func) return CCOL_STATUS_PRINT_FUNC;
    if (vec->size == 0) {
        printf("[]\n");
        return CCOL_STATUS_OK;
    }

    printf("[");
    for (size_t i = 0; i < vec->size; i++) {
        void *element = (char *)vec->data + (i * vec->element_size);
        vec->printer.func(element, vec->printer.ctx);
        if (i < vec->size - 1) printf(", ");
    }
    printf("]\n");

    return CCOL_STATUS_OK;
}
