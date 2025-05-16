/*
 * ccol/ccol_cdll_iterator.h
 *
 * Iterator API for circular doubly-linked list (cdll).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_CDLL_ITERATOR_H
#define CCOL_CDLL_ITERATOR_H

#include "ccol_cdll.h"
#include "ccol_iterator.h"

typedef struct ccol_cdll_iterator_state {
    const ccol_cdll_t *cdll;
    ccol_dll_node_t *current;
    size_t step;
} ccol_cdll_iterator_state_t;

ccol_iterator_t *ccol_cdll_iterator_create(const ccol_cdll_t *cdll);

#define CCOL_CDLL_FOR(type, var, cdll_ptr)                                               \
    for (ccol_iterator_t *_it = ccol_cdll_iterator_create(cdll_ptr); _it; _it = NULL)    \
        for (type *var = NULL;                                                           \
            _it->has_next(_it) &&                                                        \
            ((var = (type *)_it->next(_it)) || 1);)                                      \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif  // CCOL_CDLL_ITERATOR_H
