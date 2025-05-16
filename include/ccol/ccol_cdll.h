/*
 * ccol/ccol_cdll.h
 *
 * Circular doubly linked list (cdll) API.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_CDLL_H
#define CCOL_CDLL_H

#include <stddef.h>
#include <stdbool.h>

#include "ccol_status.h"
#include "ccol_constants.h"
#include "ccol_iterator.h"
#include "ccol_dll.h"

typedef struct ccol_cdll {
    ccol_dll_node_t *head;
    ccol_dll_node_t *tail;
    size_t size;

    ccol_copy_t copier;
    ccol_free_t freer;
    ccol_print_t printer;
    ccol_comparator_t comparator;

    bool is_initialized;
} ccol_cdll_t;

// Create / Initialize
ccol_status_t ccol_cdll_init(
    ccol_cdll_t *cdll,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

ccol_status_t ccol_cdll_create(
    ccol_cdll_t **cdll_out,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

// Insertion
ccol_status_t ccol_cdll_push(ccol_cdll_t *cdll, void *data);
ccol_status_t ccol_cdll_push_front(ccol_cdll_t *cdll, void *data);
ccol_status_t ccol_cdll_push_middle(ccol_cdll_t *cdll, void *data);
ccol_status_t ccol_cdll_push_back(ccol_cdll_t *cdll, void *data);

ccol_status_t ccol_cdll_insert_before(ccol_cdll_t *cdll, ccol_dll_node_t* ref_node, void *data);
ccol_status_t ccol_cdll_insert_after(ccol_cdll_t *cdll, ccol_dll_node_t* ref_node, void *data);

// Removal
ccol_status_t ccol_cdll_pop(ccol_cdll_t *cdll, void **data_out);
ccol_status_t ccol_cdll_pop_front(ccol_cdll_t *cdll, void **data_out);
ccol_status_t ccol_cdll_pop_middle(ccol_cdll_t *cdll, void **data_out);
ccol_status_t ccol_cdll_pop_back(ccol_cdll_t *cdll, void **data_out);

ccol_status_t ccol_cdll_remove_node(ccol_cdll_t *cdll, ccol_dll_node_t* node);
ccol_status_t ccol_cdll_remove(ccol_cdll_t *cdll, void *data);

// Access
ccol_status_t ccol_cdll_get(const ccol_cdll_t *cdll, size_t index, void **data_out);
ccol_status_t ccol_cdll_get_node(const ccol_cdll_t *cdll, size_t index, ccol_dll_node_t **node_out);

ccol_status_t ccol_cdll_peek(const ccol_cdll_t *cdll, void **data_out);
ccol_status_t ccol_cdll_peek_front(const ccol_cdll_t *cdll, void **data_out);
ccol_status_t ccol_cdll_peek_middle(const ccol_cdll_t *cdll, void **data_out);
ccol_status_t ccol_cdll_peek_back(const ccol_cdll_t *cdll, void **data_out);

ccol_dll_node_t *ccol_cdll_search(const ccol_cdll_t *cdll, const void *data);

// Attributes
bool ccol_cdll_is_empty(const ccol_cdll_t *cdll);
size_t ccol_cdll_size(const ccol_cdll_t *cdll);

bool ccol_cdll_contains(const ccol_cdll_t *cdll, const void *data);
bool ccol_cdll_contains_node(const ccol_cdll_t *cdll, const ccol_dll_node_t *node);

// Indexing
ccol_status_t ccol_cdll_safe_index_of(const ccol_cdll_t *cdll, void *data, size_t *out_index);
size_t ccol_cdll_index_of(const ccol_cdll_t *cdll, void *data);

// Utilities
ccol_status_t ccol_cdll_set(ccol_cdll_t *cdll, size_t index, void *data);

ccol_status_t ccol_cdll_swap_data(ccol_cdll_t *cdll, size_t i, size_t j);
ccol_status_t ccol_cdll_swap_nodes(ccol_cdll_t *cdll, ccol_dll_node_t *x, ccol_dll_node_t *y);

ccol_status_t ccol_cdll_reverse(ccol_cdll_t *cdll);

// Copy / Clone
ccol_status_t ccol_cdll_clone(const ccol_cdll_t *src, ccol_cdll_t **cdll_out);
ccol_status_t ccol_cdll_deep_clone(const ccol_cdll_t *src, ccol_cdll_t **cdll_out);
ccol_status_t ccol_cdll_shallow_clone(const ccol_cdll_t *src, ccol_cdll_t **cdll_out);

ccol_status_t ccol_cdll_copy(ccol_cdll_t *dest, const ccol_cdll_t *src);
ccol_status_t ccol_cdll_deep_copy(ccol_cdll_t *dest, const ccol_cdll_t *src);
ccol_status_t ccol_cdll_shallow_copy(ccol_cdll_t *dest, const ccol_cdll_t *src);

// Cleanup
ccol_status_t ccol_cdll_clear(ccol_cdll_t *cdll);
ccol_status_t ccol_cdll_destroy(ccol_cdll_t *cdll);
ccol_status_t ccol_cdll_free(ccol_cdll_t **cdll_ptr);

// Print / Debug
ccol_status_t ccol_cdll_print(const ccol_cdll_t *cdll);

#endif  // CCOL_CDLL_H
