/*
 * ccol/cdll_iterator.h
 *
 * Iterator functions for cdll
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CDLL_ITERATOR_H
#define CDLL_ITERATOR_H

#include "cdll.h"
#include "iterator.h"

typedef struct {
    const cdll_t *cdll;
    dll_node_t *current;
    size_t step;
} cdll_iterator_state_t;

iterator_t *cdll_iterator_create(const cdll_t *cdll);

#define CDLL_FOR(type, var, cdll_ptr)                                             \
    for (iterator_t *_it = cdll_iterator_create(cdll_ptr); _it; _it = NULL)       \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif //CDLL_ITERATOR_H
