/*
 * ccol/ccol_queue_iterator.h
 *
 * Iterator for queue.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_QUEUE_ITERATOR_H
#define CCOL_QUEUE_ITERATOR_H

#include "ccol_queue.h"
#include "ccol_iterator.h"

typedef struct ccol_queue_iterator_state {
    const ccol_queue_t *queue;
    ccol_dll_node_t *current;
    size_t step;
} ccol_queue_iterator_state_t;

ccol_iterator_t *ccol_queue_iterator_create(const ccol_queue_t *queue);

#define CCOL_QUEUE_FOR(type, var, queue_ptr)                                               \
    for (ccol_iterator_t *_it = ccol_queue_iterator_create(queue_ptr); _it; _it = NULL)    \
        for (type *var = NULL;                                                             \
            _it->has_next(_it) &&                                                          \
            ((var = (type *)_it->next(_it)) || 1);)                                        \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif  // CCOL_QUEUE_ITERATOR_H
