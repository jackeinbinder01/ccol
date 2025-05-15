/*
 * ccol/iterator.h
 *
 * Generic iterator
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>

typedef struct iterator_t {
    void *container;
    void *state;
    bool (*has_next)(struct iterator_t *iter); // 1 if true, 0 if false
    void *(*next)(struct iterator_t *iter); // returns next element
    void (*destroy)(struct iterator_t *iter); // frees memory
} iterator_t;

#endif // ITERATOR_H
