/*
 * ccol/vector_iterator.h
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef VECTOR_ITERATOR_H
#define VECTOR_ITERATOR_H

#include "vector.h"
#include "iterator.h"

typedef struct {
    const vector_t *vec;
    size_t current;
} vector_iterator_state_t;

iterator_t *vector_iterator_create(const vector_t *vec);

#define VEC_FOR(type, var, vec_ptr)                                             \
    for (iterator_t *_it = vector_iterator_create(vec_ptr); _it; _it = NULL)    \
        for (type *var = NULL;                                                  \
            _it->has_next(_it) &&                                               \
            ((var = (type *)_it->next(_it)) || 1);)                             \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif //VECTOR_ITERATOR_H
