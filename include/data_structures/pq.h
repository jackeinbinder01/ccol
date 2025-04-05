/*
 * ccol/pq.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "heap.h"
#include "comparator.h"

typedef struct pq_t {
    heap_t *heap;
    bool is_initialized;
} pq_t;

// Constructors
void pq_init(pq_t *pq);
pq_t *pq_create(heap_type_t heap_type, comparator_t cmp);
pq_t *pq_build(vector_t *vec, heap_type_t heap_type, comparator_t cmp);

// Insertion
void pq_enqueue(pq_t *pq, void *data);

// Removal
void *pq_dequeue(pq_t *pq);
void pq_remove(pq_t *pq, void *data);

// Access
void *pq_peek(const pq_t *pq);

// Attributes
size_t pq_size(const pq_t *pq);
bool pq_is_empty(const pq_t *pq);
bool pq_contains(const pq_t *pq, void *data);

// Utilities
pq_t *pq_clone(const pq_t *pq);
void pq_copy(pq_t *dest, const pq_t *src);
void pq_update_key(pq_t *pq, void *data, void *key);
void pq_replace(pq_t *pq, void *data);

// Print
void pq_print(const pq_t *pq);

// Cleanup
void pq_free(pq_t *pq);
void pq_destroy(pq_t *pq, void (*free_data)(void *));
void pq_clear(pq_t *pq, void (*free_data)(void *));

// Iterator
iterator_t *pq_iterator_create(const pq_t *pq);

#define PQ_FOR(type, var, pq_ptr)                                                 \
    for (iterator_t *_it = pq_iterator_create(pq_ptr); _it; _it = NULL)           \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // PQ_H
