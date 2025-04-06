/*
 * ccol/dll.h
 *
 * Doubly-linked list
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dll.h"
#include "ccol_status.h"

// Constructors
ccol_status_t dll_create(dll_t **dll_out) {
    if (!dll_out) return CCOL_STATUS_INVALID_ARG;

    dll_t* dll = malloc(sizeof(dll_t));
    if (!dll) return CCOL_STATUS_ALLOC;

    dll_init(dll);
    *dll_out = dll;
    return CCOL_STATUS_SUCCESS;
}

ccol_status_t dll_init(dll_t *dll) {
    if (!dll) return CCOL_STATUS_INVALID_ARG;

    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    dll->is_initialized = true;

    return CCOL_STATUS_SUCCESS;
}

// Insertion
ccol_status_t dll_push_back(dll_t *dll, void *data) {

}





ccol_status_t dll_push_middle(dll_t *dll, void *data);
ccol_status_t dll_push_front(dll_t *dll, void *data);
ccol_status_t dll_insert_after(dll_t *dll, dll_node_t* ref_node, void *data);
ccol_status_t dll_insert_before(dll_t *dll, dll_node_t* ref_node, void *data);

// Removal
ccol_status_t dll_remove(dll_t *dll, void *data);
void dll_remove_node(dll_t *dll, dll_node_t* node);
void *dll_pop(dll_t *dll);
void *dll_pop_middle(dll_t *dll);
void *dll_pop_front(dll_t *dll);

// Access
void *dll_get(const dll_t *dll, size_t index);
void *dll_search(const dll_t *dll, const void *data, int (*cmp)(const void *, const void *));
void *dll_peek_back(const dll_t *dll);
void *dll_peek_middle(const dll_t *dll);
void *dll_peek_front(const dll_t *dll);

// Attributes
size_t dll_size(const dll_t *dll);
bool dll_is_empty(const dll_t *dll);
bool dll_contains(const dll_t *dll, void *data);

// Print
void dll_print(const dll_t *dll);

// Cleanup
void dll_destroy(dll_t *dll, void (*free_data)(void*));
void dll_free(dll_t *dll);
void dll_clear(dll_t *dll, void (*free_data)(void *));

// Utilities
ccol_status_t dll_set(dll_t *dll, size_t index, void *data);
ccol_status_t dll_clone(const dll_t *src, dll_t **dll_out);
ccol_status_t dll_copy(dll_t *dest, const dll_t *src);
ccol_status_t dll_swap(dll_t *dll, size_t i, size_t j);
size_t dll_index_of(const dll_t *dll, void *data);
ccol_status_t dll_reverse(dll_t *dll);

// Iterator
iterator_t *dll_iterator_create(const dll_t *dll);

