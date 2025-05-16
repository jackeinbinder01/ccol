/*
 * ccol/ccol_deque_iterator.h
 *
 * Iterator API for double-ended queue (deque).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_DEQUE_ITERATOR_H
#define CCOL_DEQUE_ITERATOR_H

#include "ccol_iterator.h"
#include "ccol_deque.h"

typedef struct ccol_deque_iterator_state {
    const ccol_deque_t *deque;
    ccol_dll_node_t *current;
    size_t step;
} ccol_deque_iterator_state_t;

// Iterator
ccol_iterator_t *ccol_deque_iterator_create(const ccol_deque_t *deque);

#define CCOL_DEQUE_FOR(type, var, deque_ptr)                                               \
    for (ccol_iterator_t *_it = ccol_deque_iterator_create(deque_ptr); _it; _it = NULL)    \
        for (type *var = NULL;                                                             \
            _it->has_next(_it) &&                                                          \
            ((var = (type *)_it->next(_it)) || 1);)                                        \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif  // CCOL_DEQUE_ITERATOR_H
