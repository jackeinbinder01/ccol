/*
 * ccol/cdll.h
 *
 * Circular doubly linked list
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CDLL_H
#define CDLL_H

#include <stddef.h>
#include <stdbool.h>
#include "ccol_status.h"
#include "iterator.h"

typedef struct cdll_node_t {
    void *data;
    struct cdll_node_t *next;
    struct cdll_node_t *prev;
} cdll_node_t;

typedef struct cdll_t {
    cdll_node_t *head;
    cdll_node_t *tail;
    size_t size;

    bool is_initialized;
} cdll_t;

// Constructors
ccol_status_t cdll_init(cdll_t *cdll);
ccol_status_t cdll_create(cdll_t **cdll_out);

// Insertion
ccol_status_t cdll_push_back(cdll_t *cdll, void *data);
ccol_status_t cdll_push_middle(cdll_t *cdll, void *data);
ccol_status_t cdll_push_front(cdll_t *cdll, void *data);
ccol_status_t cdll_insert_after(cdll_t *cdll, cdll_node_t *ref_node, void *data);
ccol_status_t cdll_insert_before(cdll_t *cdll, cdll_node_t *ref_node, void *data);

// Removal
ccol_status_t cdll_remove(cdll_t *cdll, void *data);
ccol_status_t cdll_remove_node(cdll_t *cdll, cdll_node_t *node);
void *cdll_pop(cdll_t *cdll);
void *cdll_pop_middle(cdll_t *cdll);
void *cdll_pop_front(cdll_t *cdll);

// Access
void *cdll_get(const cdll_t *cdll, size_t index);
dll_node_t *cdll_search(const cdll_t *cdll, const void *data, int (*cmp)(const void *, const void *));
void *cdll_peek_back(const cdll_t *cdll);
void *cdll_peek_middle(const cdll_t *cdll);
void *cdll_peek_front(const cdll_t *cdll);
cdll_node_t *cdll_next(const cdll_t *cdll, cdll_node_t *node);
cdll_node_t *cdll_prev(const cdll_t *cdll, cdll_node_t *node);

// Attributes
size_t cdll_size(const cdll_t *cdll);
bool cdll_is_empty(const cdll_t *cdll);
bool cdll_contains(const cdll_t *cdll, void *data, int (*cmp)(const void *, const void *));

// Print
void cdll_print(const cdll_t *cdll);

// Cleanup
void cdll_destroy(cdll_t *cdll, void (*free_data)(void *));
void cdll_free(cdll_t *cdll);
void cdll_clear(cdll_t *cdll, void (*free_data)(void *));

// Utilities
ccol_status_t cdll_set(cdll_t *cdll, size_t index, void *data);
ccol_status_t cdll_clone(const cdll_t *src, cdll_t **cdll_out);
ccol_status_t cdll_copy(cdll_t *dest, const cdll_t *src);
ccol_status_t cdll_swap(cdll_t *cdll, size_t i, size_t j);
size_t cdll_index_of(const cdll_t *cdll, void *data);
ccol_status_t cdll_reverse(cdll_t *cdll);

// Iterator
iterator_t *cdll_iterator_create(const cdll_t *cdll);

#define CDLL_FOR(type, var, cdll_ptr)                                             \
    for (iterator_t *_it = cdll_iterator_create(cdll_ptr); _it; _it = NULL)       \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // CDLL_H
