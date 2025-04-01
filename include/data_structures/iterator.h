/*
 * ccol/iterator.h
 *
 * Generic iterator
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef ITERATOR_H
#define ITERATOR_H

typedef struct iterator_t {
    void* container;
    void* state;
    int (*has_next)(struct iterator_t* iter); // 1 if true, 0 if false
    void* (*next)(struct iterator_t* iter); // returns next element
    void (*destroy)(struct iterator_t* iter); // frees memory
} iterator_t;

#endif // ITERATOR_H
