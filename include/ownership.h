/*
 * ccol/ownership.h
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef OWNERSHIP_H
#define OWNERSHIP_H

#include <stdbool.h>

typedef enum ownership {
    CCOL_ORIGINAL,
    CCOL_DEEP_CLONE,
    CCOL_DEEP_COPY,
    CCOL_SHALLOW_CLONE,
    CCOL_SHALLOW_COPY,
} ccol_ownership_t;

static inline bool ccol_is_shallow(ccol_ownership_t ownership) {
    return ownership == CCOL_SHALLOW_CLONE || ownership == CCOL_SHALLOW_COPY;
}

static inline bool ccol_is_deep(ccol_ownership_t ownership) {
    return ownership == CCOL_DEEP_CLONE || ownership == CCOL_DEEP_COPY;
}

#endif //OWNERSHIP_H
