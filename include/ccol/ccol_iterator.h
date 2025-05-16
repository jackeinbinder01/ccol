/*
 * ccol/ccol_iterator.h
 *
 * Iterator API.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_ITERATOR_H
#define CCOL_ITERATOR_H

#include <stdbool.h>

typedef struct ccol_iterator {
    void *container;
    void *state;
    bool (*has_next)(struct ccol_iterator *iter); // 1 if true, 0 if false
    void *(*next)(struct ccol_iterator *iter); // returns next element
    void (*destroy)(struct ccol_iterator *iter); // frees memory
} ccol_iterator_t;

#endif  // CCOL_ITERATOR_H
