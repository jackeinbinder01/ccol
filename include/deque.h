/*
 * ccol/deque.h
 *
 * Double ended queue
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>
#include <stdbool.h>
#include "ccol_status.h"
#include "iterator.h"
#include "cdll.h"

typedef struct deque_t {
    cdll_t list;
    bool is_initialized;
} deque_t;

// Constructors
ccol_status_t deque_init(deque_t *deque);
ccol_status_t deque_create(deque_t **deque_out);

// Insertion
ccol_status_t deque_push(deque_t *deque, void *data);
ccol_status_t deque_push_front(deque_t *deque, void *data);
ccol_status_t deque_push_middle(deque_t *deque, void *data);
ccol_status_t deque_push_back(deque_t *deque, void *data);

// Removal
void *deque_pop(deque_t *deque);
void *deque_pop_front(deque_t *deque);
void *deque_pop_middle(deque_t *deque);
void *deque_pop_back(deque_t *deque);

ccol_status_t deque_remove(deque_t *deque, void *data);

// Access
void *deque_get(const deque_t *deque, size_t index);
dll_node_t *deque_search(const deque_t *deque, const void *data, int (*cmp)(const void *, const void *));
void *deque_peek_back(const deque_t *deque);
void *deque_peek_middle(const deque_t *deque);
void *deque_peek_front(const deque_t *deque);

// Attributes
size_t deque_size(const deque_t *deque);
bool deque_is_empty(const deque_t *deque);
bool deque_contains(const deque_t *deque, void *data, int (*cmp)(const void *, const void *));

// Print
void deque_print(const deque_t *deque);

// Cleanup
void deque_destroy(deque_t *deque, void (*free_data)(void *));
void deque_free(deque_t *deque);
void deque_clear(deque_t *deque, void (*free_data)(void *));

// Utilities
ccol_status_t deque_set(deque_t *deque, size_t index, void *data);
ccol_status_t deque_clone(const deque_t *src, deque_t **deque_out);
ccol_status_t deque_copy(deque_t *dest, const deque_t *src);
ccol_status_t deque_swap(deque_t *deque, size_t i, size_t j);
size_t deque_index_of(const deque_t *deque, void *data);
ccol_status_t deque_reverse(deque_t *deque);

// Iterator
iterator_t *deque_iterator_create(const deque_t *deque);

#define DEQUE_FOR(type, var, deque_ptr)                                           \
    for (iterator_t *_it = deque_iterator_create(deque_ptr); _it; _it = NULL)     \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // DEQUE_H
