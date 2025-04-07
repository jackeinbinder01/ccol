/*
 * ccol/ccol_status.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef CCOL_STATUS_H
#define CCOL_STATUS_H

typedef enum {
    CCOL_STATUS_OK = 0,
    CCOL_STATUS_ALLOC,
    CCOL_STATUS_UNINITIALIZED,
    CCOL_STATUS_INVALID_ARG,
    CCOL_STATUS_OUT_OF_BOUNDS,
    CCOL_STATUS_UNDERFLOW,
    CCOL_STATUS_OVERFLOW,
    CCOL_STATUS_NOT_FOUND,
    CCOL_STATUS_FULL,
    CCOL_STATUS_EMPTY,
    CCOL_STATUS_ERROR,
} ccol_status_t;

const char *ccol_strstatus(ccol_status_t status);

#endif // CCOL_STATUS_H
