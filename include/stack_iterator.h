/*
 * ccol/stack_iterator.h
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef STACK_ITERATOR_H
#define STACK_ITERATOR_H

#include "stack.h"
#include "iterator.h"

typedef struct {
    const stack_t *stack;
    dll_node_t *current;
    size_t step;
} stack_iterator_state_t;

iterator_t *stack_iterator_create(const stack_t *stack);

#define STACK_FOR(type, var, stack_ptr)                                           \
    for (iterator_t *_it = stack_iterator_create(stack_ptr); _it; _it = NULL)     \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif //STACK_ITERATOR_H
