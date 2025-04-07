/*
 * ccol/dll_iterator.h
 *
 * Iterator functions for dll
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef DLL_ITERATOR_H
#define DLL_ITERATOR_H

#include "dll.h"
#include "iterator.h"

typedef struct {
    const dll_t *dll;
    dll_node_t *current;
} dll_iterator_state_t;

iterator_t *dll_iterator_create(const dll_t *dll);

#define DLL_FOR(type, var, dll_ptr)                                               \
    for (iterator_t *_it = dll_iterator_create(dll_ptr); _it; _it = NULL)         \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // DLL_ITERATOR_H
