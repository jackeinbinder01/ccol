/*
 * ccol/queue_iterator.h
 *
 *
 * Created by Jack:
 *
 * Copyright (C) 2025 Jack
 *
 *
 * 
 */

#ifndef QUEUE_ITERATOR_H
#define QUEUE_ITERATOR_H

#include "queue.h"
#include "iterator.h"

typedef struct {
    const queue_t *queue;
    dll_node_t *current;
    size_t step;
} queue_iterator_state_t;

iterator_t *queue_iterator_create(const queue_t *queue);

#define QUEUE_FOR(type, var, queue_ptr)                                           \
    for (iterator_t *_it = queue_iterator_create(queue_ptr); _it; _it = NULL)     \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif //QUEUE_ITERATOR_H
