/*
 * ccol/dll.h
 *
 * Doubly linked list
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef DLL_H
#define DLL_H

#include <stddef.h>
#include <stdbool.h>
#include "ccol_status.h"
#include "iterator.h"

// Sentinal value for index not found
#define DLL_NOT_FOUND SIZE_MAX

typedef struct dll_node_t {
    void *data;
    struct dll_node_t *next;
    struct dll_node_t *prev;
} dll_node_t;

typedef struct dll_t {
    dll_node_t *head;
    dll_node_t *tail;
    size_t size;

    bool is_initialized;
} dll_t;

// Constructors
ccol_status_t dll_init(dll_t *dll);
ccol_status_t dll_create(dll_t **dll_out);

// Insertion
ccol_status_t dll_push_back(dll_t *dll, void *data);
ccol_status_t dll_push_middle(dll_t *dll, void *data);
ccol_status_t dll_push_front(dll_t *dll, void *data);
ccol_status_t dll_insert_after(dll_t *dll, dll_node_t* ref_node, void *data);
ccol_status_t dll_insert_before(dll_t *dll, dll_node_t* ref_node, void *data);

// Removal
ccol_status_t dll_remove(dll_t *dll, void *data, int (*cmp)(const void *, const void *));
ccol_status_t dll_remove_node(dll_t *dll, dll_node_t* node);
ccol_status_t dll_pop(dll_t *dll, void **data_out);
ccol_status_t dll_pop_middle(dll_t *dll, void **data_out);
ccol_status_t dll_pop_front(dll_t *dll, void **data_out);

// Access
ccol_status_t dll_get(const dll_t *dll, size_t index, void **data_out);
ccol_status_t dll_get_node(const dll_t *dll, size_t index, dll_node_t **node_out);
dll_node_t *dll_search(const dll_t *dll, const void *data, int (*cmp)(const void *, const void *));
ccol_status_t dll_peek_back(const dll_t *dll, void **data_out);
ccol_status_t dll_peek_middle(const dll_t *dll, void **data_out);
ccol_status_t dll_peek_front(const dll_t *dll, void **data_out);

// Attributes
size_t dll_size(const dll_t *dll);
bool dll_is_empty(const dll_t *dll);
bool dll_contains(const dll_t *dll, const void *data, int (*cmp)(const void *, const void *));
bool dll_contains_node(const dll_t *dll, const dll_node_t *node);

// Print
void dll_print(const dll_t *dll);

// Cleanup
void dll_destroy(dll_t *dll, void (*free_data)(void*));
void dll_free(dll_t *dll);
void dll_free_node(dll_node_t *node);
void dll_dispose_node(dll_node_t *node, void (*free_data)(void *));
void dll_clear(dll_t *dll, void (*free_data)(void *));

// Utilities
ccol_status_t dll_set(dll_t *dll, size_t index, void *data);
ccol_status_t dll_clone(const dll_t *src, dll_t **dll_out, void *(*copy_data)(const void *));
ccol_status_t dll_deep_clone(const dll_t *src, dll_t **dll_out);
ccol_status_t dll_copy(dll_t *dest, const dll_t *src, void (*free_data)(void *));
ccol_status_t dll_deep_copy(dll_t *dest, const dll_t *src, void (*free_data)(void *), void *(*copy_data)(const void *));
ccol_status_t dll_swap_data(dll_t *dll, size_t i, size_t j);
ccol_status_t dll_swap_nodes(dll_t *dll, dll_node_t *x, dll_node_t *y);
ccol_status_t dll_safe_index_of(const dll_t *dll, void *data, int (*cmp)(const void *, const void *), size_t *out_index);
size_t dll_index_of(const dll_t *dll, void *data);
ccol_status_t dll_reverse(dll_t *dll);

// Iterator
iterator_t *dll_iterator_create(const dll_t *dll);

#define DLL_FOR(type, var, dll_ptr)                                               \
    for (iterator_t *_it = dll_iterator_create(dll_ptr); _it; _it = NULL)         \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // DLL_H
