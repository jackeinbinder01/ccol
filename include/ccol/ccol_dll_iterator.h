/*
 * ccol/ccol_dll_iterator.h
 *
 * Iterator for doubly-linked list (dll).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_DLL_ITERATOR_H
#define CCOL_DLL_ITERATOR_H

#include "ccol_dll.h"
#include "ccol_iterator.h"

typedef struct ccol_dll_iterator_state {
    const ccol_dll_t *dll;
    ccol_dll_node_t *current;
} ccol_dll_iterator_state_t;

ccol_iterator_t *ccol_dll_iterator_create(const ccol_dll_t *dll);

#define CCOL_DLL_FOR(type, var, dll_ptr)                                               \
    for (ccol_iterator_t *_it = ccol_dll_iterator_create(dll_ptr); _it; _it = NULL)    \
        for (type *var = NULL;                                                         \
            _it->has_next(_it) &&                                                      \
            ((var = (type *)_it->next(_it)) || 1);)                                    \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif  // CCOL_DLL_ITERATOR_H
