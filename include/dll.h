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
#include "ccol_constants.h"
#include "ccol_status.h"
#include "ccol_constants.h"
#include "iterator.h"

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

// Create / Initialize
ccol_status_t dll_init(dll_t *dll);
ccol_status_t dll_create(dll_t **dll_out);

// Insertion
ccol_status_t dll_push(dll_t *dll, void *data);
ccol_status_t dll_push_front(dll_t *dll, void *data);
ccol_status_t dll_push_middle(dll_t *dll, void *data);
ccol_status_t dll_push_back(dll_t *dll, void *data);

ccol_status_t dll_insert_before(dll_t *dll, dll_node_t* ref_node, void *data);
ccol_status_t dll_insert_after(dll_t *dll, dll_node_t* ref_node, void *data);

// Removal
ccol_status_t dll_pop(dll_t *dll, void **data_out);
ccol_status_t dll_pop_front(dll_t *dll, void **data_out);
ccol_status_t dll_pop_middle(dll_t *dll, void **data_out);
ccol_status_t dll_pop_back(dll_t *dll, void **data_out);

ccol_status_t dll_remove_node(dll_t *dll, dll_node_t* node);
ccol_status_t dll_remove(dll_t *dll, void *data, int (*cmp)(const void *, const void *));

// Access
ccol_status_t dll_get(const dll_t *dll, size_t index, void **data_out);
ccol_status_t dll_get_node(const dll_t *dll, size_t index, dll_node_t **node_out);

ccol_status_t dll_peek(const dll_t *dll, void **data_out);
ccol_status_t dll_peek_front(const dll_t *dll, void **data_out);
ccol_status_t dll_peek_middle(const dll_t *dll, void **data_out);
ccol_status_t dll_peek_back(const dll_t *dll, void **data_out);

dll_node_t *dll_search(const dll_t *dll, const void *data, int (*cmp)(const void *, const void *));

// Attributes
bool dll_is_empty(const dll_t *dll);
size_t dll_size(const dll_t *dll);

bool dll_contains(const dll_t *dll, const void *data, int (*cmp)(const void *, const void *));
bool dll_contains_node(const dll_t *dll, const dll_node_t *node);

// Indexing
ccol_status_t dll_safe_index_of(const dll_t *dll, void *data, int (*cmp)(const void *, const void *), size_t *out_index);
size_t dll_index_of(const dll_t *dll, void *data, int (*cmp)(const void *, const void *));

// Utilities
ccol_status_t dll_set(dll_t *dll, size_t index, void *data);

ccol_status_t dll_swap_data(dll_t *dll, size_t i, size_t j);
ccol_status_t dll_swap_nodes(dll_t *dll, dll_node_t *x, dll_node_t *y);

ccol_status_t dll_reverse(dll_t *dll);

// Copy / Clone
ccol_status_t dll_clone(const dll_t *src, dll_t **dll_out, void *(*copy_data)(const void *));
ccol_status_t dll_deep_clone(const dll_t *src, dll_t **dll_out);
ccol_status_t dll_copy(dll_t *dest, const dll_t *src, void (*free_data)(void *), void *(*copy_data)(const void *));
ccol_status_t dll_deep_copy(dll_t *dest, const dll_t *src, void (*free_data)(void *));

// Cleanup
void dll_clear(dll_t *dll, void (*free_data)(void *));
void dll_destroy(dll_t *dll, void (*free_data)(void*));
void dll_free(dll_t *dll, void (*free_data)(void*));

// Print / Debug
ccol_status_t dll_print(const dll_t *dll, void (*print_data)(const void *));

#endif // DLL_H
