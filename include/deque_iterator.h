/*
 * ccol/deque_iterator.h
 *
 * Iterator functions for deque
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef DEQUE_ITERATOR_H
#define DEQUE_ITERATOR_H

#include "iterator.h"
#include "deque.h"

typedef struct {
    const deque_t *deque;
    dll_node_t *current;
    size_t step;
} deque_iterator_state_t;

// Iterator
iterator_t *deque_iterator_create(const deque_t *deque);

#define DEQUE_FOR(type, var, deque_ptr)                                           \
    for (iterator_t *_it = deque_iterator_create(deque_ptr); _it; _it = NULL)     \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // DEQUE_ITERATOR_H
