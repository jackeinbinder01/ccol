/*
 * ccol/ccol_macros.h
 *
 * All CCOl macros
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_MACROS_H
#define CCOL_MACROS_H

#include "ccol_status.h"

// Iterator pattern
#define CCOL_ITER_FOR(type, var, iter_ptr)                              \
    for (iterator_t *_it = (iter_ptr); _it; _it = NULL)                 \
        for (type *var = NULL;                                          \
            _it->has_next(_it) &&                                       \
            ((var = (type *)_it->next(_it)) || 1);)                     \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

// Check initialized
#define CCOL_CHECK_INIT(ptr)                                            \
    do {                                                                \
        if (!(ptr))                 return CCOL_STATUS_INVALID_ARG;     \
        if (!(ptr->is_initialized)) return CCOL_STATUS_UNINITIALIZED;   \
    } while (0)

#define COPY_DEFAULT copy_identity

#define SWAP_PTR(x, y) swap((void *)&(x), (void *)&(y), sizeof(x));

#endif // CCOL_MACROS_H
