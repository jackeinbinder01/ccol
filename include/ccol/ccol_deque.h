/*
 * ccol/ccol_deque.h
 *
 * Double ended queue (deque) API.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_DEQUE_H
#define CCOL_DEQUE_H

#include <stddef.h>
#include <stdbool.h>

#include "ccol_constants.h"
#include "ccol_status.h"
#include "ccol_iterator.h"
#include "ccol_cdll.h"

typedef struct ccol_deque_t {
    ccol_cdll_t *list;
    bool is_initialized;
} ccol_deque_t;

// Create / Initialize
ccol_status_t ccol_deque_init(
    ccol_deque_t *deque,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

ccol_status_t ccol_deque_create(
    ccol_deque_t **deque_out,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

// Insertion
ccol_status_t ccol_deque_push(ccol_deque_t *deque, void *data);
ccol_status_t ccol_deque_push_front(ccol_deque_t *deque, void *data);
ccol_status_t ccol_deque_push_middle(ccol_deque_t *deque, void *data);
ccol_status_t ccol_deque_push_back(ccol_deque_t *deque, void *data);

ccol_status_t ccol_deque_insert_before(ccol_deque_t *deque, ccol_dll_node_t* ref_node, void *data);
ccol_status_t ccol_deque_insert_after(ccol_deque_t *deque, ccol_dll_node_t* ref_node, void *data);

// Removal
ccol_status_t ccol_deque_pop(ccol_deque_t *deque, void **data_out);
ccol_status_t ccol_deque_pop_front(ccol_deque_t *deque, void **data_out);
ccol_status_t ccol_deque_pop_middle(ccol_deque_t *deque, void **data_out);
ccol_status_t ccol_deque_pop_back(ccol_deque_t *deque, void **data_out);

ccol_status_t ccol_deque_remove_node(ccol_deque_t *deque, ccol_dll_node_t* node);
ccol_status_t ccol_deque_remove(ccol_deque_t *deque, void *data);

// Access
ccol_status_t ccol_deque_get(const ccol_deque_t *deque, size_t index, void **data_out);
ccol_status_t ccol_deque_get_node(const ccol_deque_t *deque, size_t index, ccol_dll_node_t **node_out);

ccol_status_t ccol_deque_peek(const ccol_deque_t *deque, void **data_out);
ccol_status_t ccol_deque_peek_front(const ccol_deque_t *deque, void **data_out);
ccol_status_t ccol_deque_peek_middle(const ccol_deque_t *deque, void **data_out);
ccol_status_t ccol_deque_peek_back(const ccol_deque_t *deque, void **data_out);

ccol_dll_node_t *ccol_deque_search(const ccol_deque_t *deque, const void *data);

// Attributes
bool ccol_deque_is_empty(const ccol_deque_t *deque);
size_t ccol_deque_size(const ccol_deque_t *deque);

bool ccol_deque_contains(const ccol_deque_t *deque, const void *data);
bool ccol_deque_contains_node(const ccol_deque_t *deque, const ccol_dll_node_t *node);

// Indexing
ccol_status_t ccol_deque_safe_index_of(const ccol_deque_t *deque, void *data, size_t *out_index);
size_t ccol_deque_index_of(const ccol_deque_t *deque, void *data);

// Utilities
ccol_status_t ccol_deque_set(ccol_deque_t *deque, size_t index, void *data);

ccol_status_t ccol_deque_swap_data(ccol_deque_t *deque, size_t i, size_t j);
ccol_status_t ccol_deque_swap_nodes(ccol_deque_t *deque, ccol_dll_node_t *x, ccol_dll_node_t *y);

ccol_status_t ccol_deque_reverse(ccol_deque_t *deque);

// Copy / Clone
ccol_status_t ccol_deque_clone(const ccol_deque_t *src, ccol_deque_t **deque_out);
ccol_status_t ccol_deque_deep_clone(const ccol_deque_t *src, ccol_deque_t **deque_out);
ccol_status_t ccol_deque_shallow_clone(const ccol_deque_t *src, ccol_deque_t **deque_out);

ccol_status_t ccol_deque_copy(ccol_deque_t *dest, const ccol_deque_t *src);
ccol_status_t ccol_deque_deep_copy(ccol_deque_t *dest, const ccol_deque_t *src);
ccol_status_t ccol_deque_shallow_copy(ccol_deque_t *dest, const ccol_deque_t *src);

// Cleanup
ccol_status_t ccol_deque_clear(ccol_deque_t *deque);
ccol_status_t ccol_deque_destroy(ccol_deque_t *deque);
ccol_status_t ccol_deque_free(ccol_deque_t **deque_ptr);

// Print / Debug
ccol_status_t ccol_deque_print(const ccol_deque_t *deque);

#endif  // CCOL_DEQUE_H
