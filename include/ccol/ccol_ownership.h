/*
 * ccol/ccol_ownership.h
 *
 * Container data ownership and original/deep/shallow status.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_OWNERSHIP_H
#define CCOL_OWNERSHIP_H

#include <stdbool.h>

typedef enum ccol_ownership {
    CCOL_ORIGINAL,
    CCOL_DEEP_CLONE,
    CCOL_DEEP_COPY,
    CCOL_SHALLOW_CLONE,
    CCOL_SHALLOW_COPY,
} ccol_ownership_t;

static inline const char *ccol_ownership_to_string(ccol_ownership_t ownership) {
    switch(ownership) {
        case CCOL_ORIGINAL:         return "CCOL_ORIGINAL";
        case CCOL_DEEP_CLONE:       return "CCOL_DEEP_CLONE";
        case CCOL_DEEP_COPY:        return "CCOL_DEEP_COPY";
        case CCOL_SHALLOW_CLONE:    return "CCOL_SHALLOW_CLONE";
        case CCOL_SHALLOW_COPY:     return "CCOL_SHALLOW_COPY";
        default:                    return "INVALID";
    }
}

static inline bool ccol_is_shallow(ccol_ownership_t ownership) {
    return ownership == CCOL_SHALLOW_CLONE || ownership == CCOL_SHALLOW_COPY;
}

static inline bool ccol_is_deep(ccol_ownership_t ownership) {
    return ownership == CCOL_DEEP_CLONE || ownership == CCOL_DEEP_COPY;
}

#endif  // CCOL_OWNERSHIP_H
