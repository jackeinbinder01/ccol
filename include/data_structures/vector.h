/*
 * ccol/vector.h
 *
 * Dynamic array
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include "iterator.h"

typedef struct vector {
  void* data;
  size_t size;
  size_t capacity;
  size_t element_size;
} vector_t;

// Constructors
void vector_init(vector_t* vec, size_t capacity, size_t element_size);
vector_t* vector_create(size_t capacity, size_t element_size);

// Fill
void vector_fill(vector_t* vec, void* value, size_t count);

// Insertion
void vector_append(vector_t* vec, void* data);
void vector_insert(vector_t* vec, size_t index, void* data);
void vector_insert_middle(vector_t* vec, size_t index, void* data);

// Removal
void* vector_remove(vector_t* vec, size_t index);
void* vector_pop(vector_t* vec);
void* vector_pop_middle(vector_t* vec);
void* vector_pop_front(vector_t* vec);

// Access
void* vector_get(const vector_t* vec, size_t index);
void* vector_peek_back(const vector_t* vec);
void* vector_peek_middle(const vector_t* vec);
void* vector_peek_front(const vector_t* vec);

// Attributes
size_t vector_size(const vector_t* vec);
size_t vector_capacity(const vector_t* vec);
int vector_is_empty(const vector_t* vec);
int vector_is_full(const vector_t* vec);
int vector_contains(const vector_t* vec, void* data);

// Print
void vector_print(const vector_t* vec);

// Cleanup
void vector_free(vector_t* vec);
void vector_destroy(vector_t* vec, void (*free_data)(void*));
void vector_clear(vector_t* vec);

// Utilities
vector_t* vector_clone(const vector_t* vec);
void vector_set(vector_t* vec, size_t index, void* value);
void vector_swap(vector_t* vec, size_t i, size_t j);
void vector_reserve(vector_t* vec, size_t new_capacity);
void vector_shrink_to_fit(vector_t* vec);

// Iterator
iterator_t* vector_iterator_create(const vector_t* vec);

#define VEC_FOR(type, var, vec_ptr)                                             \
    for (iterator_t* _it = vector_iterator_create(vec_ptr); _it; _it = NULL)    \
        for (type* var = NULL;                                                  \
            _it->has_next(_it) &&                                               \
            ((var = (type*)_it->next(_it)) || 1);)                              \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // VECTOR_H