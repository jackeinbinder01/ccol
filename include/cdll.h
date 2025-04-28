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
#include "ccol_constants.h"
#include "iterator.h"
#include "dll.h"

typedef struct cdll_t {
    dll_node_t *head;
    dll_node_t *tail;
    size_t size;

    bool is_initialized;
} cdll_t;

// Create / Initialize
ccol_status_t cdll_init(cdll_t *cdll);
ccol_status_t cdll_create(cdll_t **cdll_out);

// Insertion
ccol_status_t cdll_push(cdll_t *cdll, void *data);
ccol_status_t cdll_push_front(cdll_t *cdll, void *data);
ccol_status_t cdll_push_middle(cdll_t *cdll, void *data);
ccol_status_t cdll_push_back(cdll_t *cdll, void *data);

ccol_status_t cdll_insert_before(cdll_t *cdll, dll_node_t* ref_node, void *data);
ccol_status_t cdll_insert_after(cdll_t *cdll, dll_node_t* ref_node, void *data);

// Removal
ccol_status_t cdll_pop(cdll_t *cdll, void **data_out);
ccol_status_t cdll_pop_front(cdll_t *cdll, void **data_out);
ccol_status_t cdll_pop_middle(cdll_t *cdll, void **data_out);
ccol_status_t cdll_pop_back(cdll_t *cdll, void **data_out);

ccol_status_t cdll_remove_node(cdll_t *cdll, dll_node_t* node, free_func_t free_data, void *ctx);
ccol_status_t cdll_remove(cdll_t *cdll, void *data, comparator_t cmp, free_func_t free_data, void *ctx);

// Access
ccol_status_t cdll_get(const cdll_t *cdll, size_t index, void **data_out);
ccol_status_t cdll_get_node(const cdll_t *cdll, size_t index, dll_node_t **node_out);

ccol_status_t cdll_peek(const cdll_t *cdll, void **data_out);
ccol_status_t cdll_peek_front(const cdll_t *cdll, void **data_out);
ccol_status_t cdll_peek_middle(const cdll_t *cdll, void **data_out);
ccol_status_t cdll_peek_back(const cdll_t *cdll, void **data_out);

dll_node_t *cdll_search(const cdll_t *cdll, const void *data, comparator_t cmp, void *ctx);

// Attributes
bool cdll_is_empty(const cdll_t *cdll);
size_t cdll_size(const cdll_t *cdll);

bool cdll_contains(const cdll_t *cdll, const void *data, comparator_t cmp, void *ctx);
bool cdll_contains_node(const cdll_t *cdll, const dll_node_t *node);

// Indexing
ccol_status_t cdll_safe_index_of(const cdll_t *cdll, void *data, comparator_t cmp, void *ctx, size_t *out_index);
size_t cdll_index_of(const cdll_t *cdll, void *data, comparator_t cmp, void *ctx);

// Utilities
ccol_status_t cdll_set(cdll_t *cdll, size_t index, void *data);

ccol_status_t cdll_swap_data(cdll_t *cdll, size_t i, size_t j);
ccol_status_t cdll_swap_nodes(cdll_t *cdll, dll_node_t *x, dll_node_t *y);

ccol_status_t cdll_reverse(cdll_t *cdll);

// Copy / Clone
ccol_status_t cdll_clone(const cdll_t *src, cdll_t **cdll_out, copy_func_t copy_data, void *ctx);
ccol_status_t cdll_deep_clone(const cdll_t *src, cdll_t **cdll_out, void *ctx);
ccol_status_t cdll_copy(cdll_t *dest, const cdll_t *src, free_func_t free_data, copy_func_t copy_data, void *ctx);
ccol_status_t cdll_deep_copy(cdll_t *dest, const cdll_t *src, free_func_t free_data, void *ctx);

// Cleanup
ccol_status_t cdll_clear(cdll_t *cdll, free_func_t free_data, void *ctx);
ccol_status_t cdll_destroy(cdll_t *cdll, free_func_t free_data, void *ctx); // might return ccol_status_t later
ccol_status_t cdll_free(cdll_t **cdll_ptr, free_func_t free_data, void *ctx);

// Print / Debug
ccol_status_t cdll_print(const cdll_t *cdll, print_func_t print_data, void *ctx);

#endif //CDLL_H
