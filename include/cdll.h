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

ccol_status_t cdll_remove_node(cdll_t *cdll, dll_node_t* node);
ccol_status_t cdll_remove(cdll_t *cdll, void *data, int (*cmp)(const void *, const void *));

// Access
ccol_status_t cdll_get(const cdll_t *cdll, size_t index, void **data_out);
ccol_status_t cdll_get_node(const cdll_t *cdll, size_t index, dll_node_t **node_out);

ccol_status_t cdll_peek(const cdll_t *cdll, void **data_out);
ccol_status_t cdll_peek_front(const cdll_t *cdll, void **data_out);
ccol_status_t cdll_peek_middle(const cdll_t *cdll, void **data_out);
ccol_status_t cdll_peek_back(const cdll_t *cdll, void **data_out);

dll_node_t *cdll_search(const cdll_t *cdll, const void *data, int (*cmp)(const void *, const void *));

// Attributes
bool cdll_is_empty(const cdll_t *cdll);
size_t cdll_size(const cdll_t *cdll);

bool cdll_contains(const cdll_t *cdll, const void *data, int (*cmp)(const void *, const void *));
bool cdll_contains_node(const cdll_t *cdll, const dll_node_t *node);

// Indexing
ccol_status_t cdll_safe_index_of(const cdll_t *cdll, void *data, int (*cmp)(const void *, const void *), size_t *out_index);
size_t cdll_index_of(const cdll_t *cdll, void *data, int (*cmp)(const void *, const void *));

// Utilities
ccol_status_t cdll_set(cdll_t *cdll, size_t index, void *data);

ccol_status_t cdll_swap_data(cdll_t *cdll, size_t i, size_t j);
ccol_status_t cdll_swap_nodes(cdll_t *cdll, dll_node_t *x, dll_node_t *y);

ccol_status_t cdll_reverse(cdll_t *cdll);

// Copy / Clone
ccol_status_t cdll_clone(const cdll_t *src, cdll_t **cdll_out, void *(*copy_data)(const void *));
ccol_status_t cdll_deep_clone(const cdll_t *src, cdll_t **cdll_out);
ccol_status_t cdll_copy(cdll_t *dest, const cdll_t *src, void (*free_data)(void *), void *(*copy_data)(const void *));
ccol_status_t cdll_deep_copy(cdll_t *dest, const cdll_t *src, void (*free_data)(void *));

// Cleanup
void cdll_clear(cdll_t *cdll, void (*free_data)(void *));
void cdll_destroy(cdll_t *cdll, void (*free_data)(void*));
void cdll_free(cdll_t *cdll, void (*free_data)(void*));

// Print / Debug
ccol_status_t cdll_print(const cdll_t *cdll, void (*print_data)(const void *));

#endif //CDLL_H
