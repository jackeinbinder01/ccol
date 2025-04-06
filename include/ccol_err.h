/*
 * ccol/ccol_err.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef CCOL_ERR_H
#define CCOL_ERR_H

typedef enum {
    CCOL_OK = 0,
    CCOL_ERR_ALLOC,
    CCOL_ERR_UNINITIALIZED,
    CCOL_ERR_INVALID_ARG,
    CCOL_ERR_OUT_OF_BOUNDS,
    CCOL_ERR_UNDERFLOW,
    CCOL_ERR_OVERFLOW,
    CCOL_ERR_NOT_FOUND,
    CCOL_ERR_FULL,
    CCOL_ERR_EMPTY,
} ccol_err_t;

const char *ccol_sterror(ccol_err_t err);

#endif // CCOL_ERR_H
