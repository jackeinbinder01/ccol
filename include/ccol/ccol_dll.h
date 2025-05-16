/*
 * ccol/ccol_dll.h
 *
 * Doubly linked list (dll) API.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_DLL_H
#define CCOL_DLL_H

#include <stddef.h>
#include <stdbool.h>

#include "ccol_status.h"
#include "ccol_constants.h"
#include "ccol_iterator.h"
#include "ccol_copy.h"
#include "ccol_free.h"
#include "ccol_print.h"
#include "ccol_comparator.h"

typedef struct ccol_dll_node {
    void *data;
    struct ccol_dll_node *next;
    struct ccol_dll_node *prev;
} ccol_dll_node_t;

typedef struct ccol_dll {
    ccol_dll_node_t *head;
    ccol_dll_node_t *tail;
    size_t size;

    ccol_copy_t copier;
    ccol_free_t freer;
    ccol_print_t printer;
    ccol_comparator_t comparator;

    bool is_initialized;
} ccol_dll_t;

// Create / Initialize
ccol_status_t ccol_dll_init(
    ccol_dll_t *dll,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

ccol_status_t ccol_dll_create(
    ccol_dll_t **dll_out,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

// Insertion
ccol_status_t ccol_dll_push(ccol_dll_t *dll, void *data);
ccol_status_t ccol_dll_push_front(ccol_dll_t *dll, void *data);
ccol_status_t ccol_dll_push_middle(ccol_dll_t *dll, void *data);
ccol_status_t ccol_dll_push_back(ccol_dll_t *dll, void *data);

ccol_status_t ccol_dll_insert_before(ccol_dll_t *dll, ccol_dll_node_t* ref_node, void *data);
ccol_status_t ccol_dll_insert_after(ccol_dll_t *dll, ccol_dll_node_t* ref_node, void *data);

// Removal
ccol_status_t ccol_dll_pop(ccol_dll_t *dll, void **data_out);
ccol_status_t ccol_dll_pop_front(ccol_dll_t *dll, void **data_out);
ccol_status_t ccol_dll_pop_middle(ccol_dll_t *dll, void **data_out);
ccol_status_t ccol_dll_pop_back(ccol_dll_t *dll, void **data_out);

ccol_status_t ccol_dll_remove_node(ccol_dll_t *dll, ccol_dll_node_t* node);
ccol_status_t ccol_dll_remove(ccol_dll_t *dll, void *data);

// Access
ccol_status_t ccol_dll_get(const ccol_dll_t *dll, size_t index, void **data_out);
ccol_status_t ccol_dll_get_node(const ccol_dll_t *dll, size_t index, ccol_dll_node_t **node_out);

ccol_status_t ccol_dll_peek(const ccol_dll_t *dll, void **data_out);
ccol_status_t ccol_dll_peek_front(const ccol_dll_t *dll, void **data_out);
ccol_status_t ccol_dll_peek_middle(const ccol_dll_t *dll, void **data_out);
ccol_status_t ccol_dll_peek_back(const ccol_dll_t *dll, void **data_out);

ccol_dll_node_t *ccol_dll_search(const ccol_dll_t *dll, const void *data);

// Attributes
bool ccol_dll_is_empty(const ccol_dll_t *dll);
size_t ccol_dll_size(const ccol_dll_t *dll);

bool ccol_dll_contains(const ccol_dll_t *dll, const void *data);
bool ccol_dll_contains_node(const ccol_dll_t *dll, const ccol_dll_node_t *node);

// Indexing
ccol_status_t ccol_dll_safe_index_of(const ccol_dll_t *dll, void *data, size_t *out_index);
size_t ccol_dll_index_of(const ccol_dll_t *dll, void *data);

// Utilities
ccol_status_t ccol_dll_set(ccol_dll_t *dll, size_t index, void *data);
ccol_status_t ccol_dll_swap_data(ccol_dll_t *dll, size_t i, size_t j);
ccol_status_t ccol_dll_swap_nodes(ccol_dll_t *dll, ccol_dll_node_t *x, ccol_dll_node_t *y);
ccol_status_t ccol_dll_reverse(ccol_dll_t *dll);

// Copy / Clone
ccol_status_t ccol_dll_clone(const ccol_dll_t *src, ccol_dll_t **dll_out); // Alias for deep clone
ccol_status_t ccol_dll_deep_clone(const ccol_dll_t *src, ccol_dll_t **dll_out);
ccol_status_t ccol_dll_shallow_clone(const ccol_dll_t *src, ccol_dll_t **dll_out);

ccol_status_t ccol_dll_copy(ccol_dll_t *dest, const ccol_dll_t *src); // Alias for deep copy
ccol_status_t ccol_dll_deep_copy(ccol_dll_t *dest, const ccol_dll_t *src);
ccol_status_t ccol_dll_shallow_copy(ccol_dll_t *dest, const ccol_dll_t *src);

// Cleanup
ccol_status_t ccol_dll_clear(ccol_dll_t *dll);
ccol_status_t ccol_dll_destroy(ccol_dll_t *dll);
ccol_status_t ccol_dll_free(ccol_dll_t **dll_ptr);

// Print / Debug
ccol_status_t ccol_dll_print(const ccol_dll_t *dll);

#endif  // CCOL_DLL_H
