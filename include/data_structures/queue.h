/*
 * ccol/queue.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>
#include "iterator.h"
#include "deque.h"

typedef struct queue_t {
    deque_t deque;
    bool is_initialized;
} queue_t;

// Constructors
void queue_init(queue_t *queue);
queue_t *queue_create(void);

// Insertion
void queue_enqueue(queue_t *queue, void *data);

// Removal
void *queue_dequeue(queue_t *queue);

// Access
void *queue_peek(const queue_t *queue);

// Attributes
size_t queue_size(const queue_t *queue);
bool queue_is_empty(const queue_t *queue);
bool queue_contains(const queue_t *queue, void *data);

// Print
void queue_print(const queue_t *queue);

// Cleanup
void queue_free(queue_t *queue);
void queue_destroy(queue_t *queue, void (*free_data)(void *));
void queue_clear(queue_t *queue, void (*free_data)(void *));

// Utilities
void queue_set(queue_t *queue, size_t index, void *data);
queue_t *queue_clone(const queue_t *queue);
void queue_copy(queue_t *dest, const queue_t *src);
void queue_swap(queue_t *queue, size_t i, size_t j);
size_t queue_index_of(const queue_t *queue, void *data);
void queue_reverse(queue_t *queue);

// Iterator
iterator_t *queue_iterator_create(const queue_t *queue);

#define QUEUE_FOR(type, var, queue_ptr)                                           \
    for (iterator_t *_it = queue_iterator_create(queue_ptr); _it; _it = NULL)     \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // QUEUE_H
