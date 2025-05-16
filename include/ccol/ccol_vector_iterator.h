/*
 * ccol/ccol_vector_iterator.h
 *
 * Iterator for vector.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_VECTOR_ITERATOR_H
#define CCOL_VECTOR_ITERATOR_H

#include "ccol_vector.h"
#include "ccol_iterator.h"

typedef struct ccol_vector_iterator_state {
    const ccol_vector_t *vec;
    size_t current;
} ccol_vector_iterator_state_t;

ccol_iterator_t *ccol_vector_iterator_create(const ccol_vector_t *vec);

#define CCOL_VEC_FOR(type, var, vec_ptr)                                             	\
    for (ccol_iterator_t *_it = ccol_vector_iterator_create(vec_ptr); _it; _it = NULL)	\
        for (type *var = NULL;                                                  		\
            _it->has_next(_it) &&                                               		\
            ((var = (type *)_it->next(_it)) || 1);)                             		\
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif  // CCOL_VECTOR_ITERATOR_H
