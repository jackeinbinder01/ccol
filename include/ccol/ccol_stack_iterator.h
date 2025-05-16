/*
 * ccol/ccol_stack_iterator.h
 *
 * Iterator for stack.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_STACK_ITERATOR_H
#define CCOL_STACK_ITERATOR_H

#include "ccol_stack.h"
#include "ccol_iterator.h"

typedef struct ccol_stack_iterator_state {
    const ccol_stack_t *stack;
    ccol_dll_node_t *current;
    size_t step;
} ccol_stack_iterator_state_t;

ccol_iterator_t *ccol_stack_iterator_create(const ccol_stack_t *stack);

#define CCOL_STACK_FOR(type, var, stack_ptr)                                               \
    for (ccol_iterator_t *_it = ccol_stack_iterator_create(stack_ptr); _it; _it = NULL)    \
        for (type *var = NULL;                                                             \
            _it->has_next(_it) &&                                                          \
            ((var = (type *)_it->next(_it)) || 1);)                                        \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif  // CCOL_STACK_ITERATOR_H
