/*
 * ccol/deque.h
 *
 * Double ended queue
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>
#include <stdbool.h>

#include "ccol_constants.h"
#include "ccol_status.h"
#include "iterator.h"
#include "cdll.h"

typedef struct deque_t {
    cdll_t list;
    bool is_initialized;
} deque_t;

// Create / Initialize
ccol_status_t deque_init(deque_t *deque);
ccol_status_t deque_create(deque_t **deque_out);

// Insertion
ccol_status_t deque_push(deque_t *deque, void *data);
ccol_status_t deque_push_front(deque_t *deque, void *data);
ccol_status_t deque_push_middle(deque_t *deque, void *data);
ccol_status_t deque_push_back(deque_t *deque, void *data);

ccol_status_t deque_insert_before(deque_t *deque, dll_node_t* ref_node, void *data);
ccol_status_t deque_insert_after(deque_t *deque, dll_node_t* ref_node, void *data);

// Removal
ccol_status_t deque_pop(deque_t *deque, void **data_out);
ccol_status_t deque_pop_front(deque_t *deque, void **data_out);
ccol_status_t deque_pop_middle(deque_t *deque, void **data_out);
ccol_status_t deque_pop_back(deque_t *deque, void **data_out);

ccol_status_t deque_remove_node(deque_t *deque, dll_node_t* node, free_func_t free_data, void *ctx);
ccol_status_t deque_remove(deque_t *deque, void *data, comparator_t cmp, free_func_t free_data, void *ctx);

// Access
ccol_status_t deque_get(const deque_t *deque, size_t index, void **data_out);
ccol_status_t deque_get_node(const deque_t *deque, size_t index, dll_node_t **node_out);

ccol_status_t deque_peek(const deque_t *deque, void **data_out);
ccol_status_t deque_peek_front(const deque_t *deque, void **data_out);
ccol_status_t deque_peek_middle(const deque_t *deque, void **data_out);
ccol_status_t deque_peek_back(const deque_t *deque, void **data_out);

dll_node_t *deque_search(const deque_t *deque, const void *data, comparator_t cmp, void *ctx);

// Attributes
bool deque_is_empty(const deque_t *deque);
size_t deque_size(const deque_t *deque);

bool deque_contains(const deque_t *deque, const void *data, comparator_t cmp, void *ctx);
bool deque_contains_node(const deque_t *deque, const dll_node_t *node);

// Indexing
ccol_status_t deque_safe_index_of(const deque_t *deque, void *data, comparator_t cmp, void *ctx, size_t *out_index);
size_t deque_index_of(const deque_t *deque, void *data, comparator_t cmp, void *ctx);

// Utilities
ccol_status_t deque_set(deque_t *deque, size_t index, void *data);

ccol_status_t deque_swap_data(deque_t *deque, size_t i, size_t j);
ccol_status_t deque_swap_nodes(deque_t *deque, dll_node_t *x, dll_node_t *y);

ccol_status_t deque_reverse(deque_t *deque);

// Copy / Clone
ccol_status_t deque_clone(const deque_t *src, deque_t **deque_out, copy_func_t copy_data, void *ctx);
ccol_status_t deque_deep_clone(const deque_t *src, deque_t **deque_out, void *ctx);
ccol_status_t deque_copy(deque_t *dest, const deque_t *src, free_func_t free_data, copy_func_t copy_data, void *ctx);
ccol_status_t deque_deep_copy(deque_t *dest, const deque_t *src, free_func_t free_data, void *ctx);

// Cleanup
void deque_clear(deque_t *deque, free_func_t free_data, void *ctx);
void deque_destroy(deque_t *deque, free_func_t free_data, void *ctx);
void deque_free(deque_t *deque, free_func_t free_data, void *ctx);

// Print / Debug
ccol_status_t deque_print(const deque_t *deque, print_func_t print_data, void *ctx);

#endif // DEQUE_H
