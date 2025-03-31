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

#define ITER_FOR(type, var, iter_ptr)                         \
    for (type* var = NULL;                                    \
        (iter_ptr)->has_next(iter_ptr) &&                     \
        ((var = (type*)iter_ptr->next(iter_ptr)) || 1);)


#endif //CCOL_MACROS_H
