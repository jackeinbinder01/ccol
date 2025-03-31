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
void vector_init(vector_t* vector, size_t capacity, size_t element_size);
vector_t* vector_create(size_t capacity, size_t element_size);

// Fill
void vector_fill(vector_t* vector, void* value, size_t count);

// Insertion
void vector_append(vector_t* vector, void* data);
void vector_insert(vector_t* vector, size_t index, void* data);

// Removal
void* vector_remove(vector_t* vector, size_t index);
void* vector_pop(vector_t* vector);
void* vector_pop_front(vector_t* vector);

// Access
void* vector_get(const vector_t* vector, size_t index);
void* vector_peek_back(const vector_t* vector);
void* vector_peek_front(const vector_t* vector);

// Attributes
size_t vector_size(const vector_t* vector);
size_t vector_capacity(const vector_t* vector);
int vector_is_empty(const vector_t* vector);
int vector_is_full(const vector_t* vector);
int vector_contains(const vector_t* vector, void* data);

// Print
void vector_print(const vector_t* vector);

// Cleanup
void vector_free(vector_t* vector);
void vector_destroy(vector_t* vector);
void vector_clear(vector_t* vector);

// Iterator
iterator_t* vector_iterator_create(const vector_t* vector);

#endif // VECTOR_H