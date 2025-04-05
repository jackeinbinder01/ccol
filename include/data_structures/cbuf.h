/*
 * ccol/cbuf.h
 *
 * Circular buffer (ring buffer)
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef CBUF_H
#define CBUF_H

#include <stddef.h>
#include <pthread.h>
#include <stdbool.h>
#include "vector.h"
#include "iterator.h"

typedef enum {
    CBUF_OVERWRITE,
    CBUF_BLOCK,
    CBUF_ERROR,
} cbuf_policy_t;

typedef struct cbuf_t {
    vector_t *buffer;
    size_t capacity;
    size_t element_size;
    cbuf_policy_t policy;

    size_t head;
    size_t tail;
    size_t count;

    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;

    bool is_initialized;
} cbuf_t;

// Constructors
void cbuf_init(cbuf_t *cbuf);
cbuf_t *cbuf_create(size_t capacity, size_t element_size, cbuf_policy_t policy);
cbuf_t *cbuf_build(vector_t *vec, size_t capacity, cbuf_policy_t policy);

// Insertion
void cbuf_put(cbuf_t *cbuf, void *data);

// Removal
void *cbuf_get(cbuf_t *cbuf);

// Attributes
size_t cbuf_count(const cbuf_t *cbuf);
size_t cbuf_capacity(const cbuf_t *cbuf);
bool cbuf_is_empty(const cbuf_t *cbuf);
bool cbuf_is_full(const cbuf_t *cbuf);
bool cbuf_is_initialized(const cbuf_t *cbuf);
bool cbuf_contains(const cbuf_t *cbuf, void *data);

// Print
void cbuf_print(const cbuf_t *cbuf);

// Cleanup
void cbuf_free(cbuf_t *cbuf);
void cbuf_destroy(cbuf_t *cbuf, void (*free_data)(void *));
void cbuf_clear(cbuf_t *cbuf, void (*free_data)(void *));

// Utilities
cbuf_t *cbuf_clone(const cbuf_t *cbuf);
void cbuf_copy(cbuf_t *dest, const cbuf_t *src);
void cbuf_reverse(cbuf_t *cbuf);

// Iterator
iterator_t *cbuf_iterator_create(const cbuf_t *cbuf);

#define CBUF_FOR(type, var, cbuf_ptr)                                          \
    for (iterator_t *_it = cbuf_iterator_create(cbuf_ptr); _it; _it = NULL)    \
        for (type *var = NULL;                                                 \
            _it->has_next(_it) &&                                              \
            ((var = (type *)_it->next(_it)) || 1);)                            \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // CBUF_H
