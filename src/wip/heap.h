/*
 * ccol/heap.h
 *
 * Min/max heap
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdbool.h>
#include "vector.h"
#include "comparator.h"

typedef enum heap_type {
    HEAP_MIN,
    HEAP_MAX,
} heap_type_t;

typedef struct heap_t {
    vector_t data;
    heap_type_t type;
    comparator_t cmp;

    bool is_initialized;
} heap_t;

// Constructors
void heap_init(heap_t *heap);
heap_t *heap_create(heap_type_t type, comparator_t cmp);
heap_t *heap_build(vector_t *vec, heap_type_t type, comparator_t cmp);

// Insertion
void heap_insert(heap_t *heap, void *data);

// Removal
void *heap_extract(heap_t *heap);
void heap_remove(heap_t *heap, void *data);

// Access
void *heap_peek(const heap_t *heap);

// Attributes
size_t heap_size(const heap_t *heap);
bool heap_is_empty(const heap_t *heap);
bool heap_contains(const heap_t *heap, void *data);

// Utilities
heap_t *heap_clone(const heap_t *heap);
void heap_copy(heap_t *dest, const heap_t *src);
void heap_update_key(heap_t *heap, void *data, void *key);
void heap_replace(heap_t *heap, void *data);

// Print
void heap_print(const heap_t *heap);

// Cleanup
void heap_free(heap_t *heap);
void heap_destroy(heap_t *heap, void (*free_data)(void *));
void heap_clear(heap_t *heap, void (*free_data)(void *));

// Iterator
iterator_t *heap_iterator_create(const heap_t *heap);

#define HEAP_FOR(type, var, heap_ptr)                                             \
    for (iterator_t *_it = heap_iterator_create(heap_ptr); _it; _it = NULL)       \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // HEAP_H
