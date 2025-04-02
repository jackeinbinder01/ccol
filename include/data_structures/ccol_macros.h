/*
 * ccol/ccol_macros.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef CCOL_MACROS_H
#define CCOL_MACROS_H

#define ITER_FOR(type, var, iter_ptr)                                   \
    for (iterator_t *_it = (iter_ptr); _it; _it = NULL)                 \
        for (type *var = NULL;                                          \
            _it->has_next(_it) &&                                       \
            ((var = (type *)_it->next(_it)) || 1);)                     \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // CCOL_MACROS_H
