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

typedef struct vector {
  void* data;
  size_t size;
  size_t capacity;
  size_t element_size;
} vector_t;

// Constructors
void vector_init(vector_t* vector, size_t capacity, size_t element_size);
vector_t* vector_create(size_t capacity, size_t element_size);

// Insertion
void vector_append(vector_t* vector, void* data);
void vector_insert(vector_t* vector, size_t index, void* data);

// Removal
void* vector_remove(vector_t* vector, size_t index);
void* vector_pop(vector_t* vector);
void* vector_pop_left(vector_t* vector);

// Access
void* vector_get(vector_t* vector, size_t index);
void* vector_peek_back(vector_t* vector);
void* vector_peek_front(vector_t* vector);

// Print
void vector_print(vector_t* vector);

// Cleanup
void vector_free(vector_t* vector);
void vector_destroy(vector_t* vector);
void vector_clear(vector_t* vector);

#endif