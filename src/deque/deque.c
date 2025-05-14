/*
 * ccol/deque.c
 *
 * Double ended queue
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */
#include "deque.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "deque_internal.h"
#include "cdll.h"
#include "cdll_internal.h"
#include "dll_internal.h"
#include "ccol_status.h"
#include "ccol_macros.h"
#include "ccol_constants.h"

// Create / Initialize
ccol_status_t deque_init(
    deque_t *deque,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
) {
    if (!deque) return CCOL_STATUS_INVALID_ARG;

    deque->list = malloc(sizeof(cdll_t));
    if (!deque->list) return CCOL_STATUS_ALLOC;

    ccol_status_t status = cdll_init(deque->list, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(deque->list);
        return status;
    }

    deque->is_initialized = true;
    return CCOL_STATUS_OK;
}

ccol_status_t deque_create(
    deque_t **deque_out,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
) {
    if (!deque_out) return CCOL_STATUS_INVALID_ARG;

    *deque_out = NULL;

    deque_t *deque = calloc(1, sizeof(deque_t));
    if (!deque) return CCOL_STATUS_ALLOC;

    ccol_status_t status = deque_init(deque, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(deque);
        return status;
    }

    *deque_out = deque;
    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t deque_push(deque_t *deque, void *data) {
    return deque_push_back(deque, data);
}

ccol_status_t deque_push_front(deque_t *deque, void *data) {
    CCOL_CHECK_INIT(deque);
    return cdll_push_front(deque->list, data);
}

ccol_status_t deque_push_middle(deque_t *deque, void *data) {
    CCOL_CHECK_INIT(deque);
    return cdll_push_middle(deque->list, data);
}

ccol_status_t deque_push_back(deque_t *deque, void *data) {
    CCOL_CHECK_INIT(deque);
    return cdll_push_back(deque->list, data);
}

ccol_status_t deque_insert_before(deque_t *deque, dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(deque);
    return cdll_insert_before(deque->list, ref_node, data);
}

ccol_status_t deque_insert_after(deque_t *deque, dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(deque);
    return cdll_insert_after(deque->list, ref_node, data);
}

// Removal
ccol_status_t deque_pop(deque_t *deque, void **data_out) {
    return deque_pop_front(deque, data_out);
}

ccol_status_t deque_pop_front(deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return cdll_pop_front(deque->list, data_out);
}

ccol_status_t deque_pop_middle(deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return cdll_pop_middle(deque->list, data_out);
}

ccol_status_t deque_pop_back(deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return cdll_pop_back(deque->list, data_out);
}

ccol_status_t deque_remove_node(deque_t *deque, dll_node_t* node) {
    CCOL_CHECK_INIT(deque);
    return cdll_remove_node(deque->list, node);
}

ccol_status_t deque_remove(deque_t *deque, void *data) {
    CCOL_CHECK_INIT(deque);
    return cdll_remove(deque->list, data);
}

// Access
ccol_status_t deque_get(const deque_t *deque, size_t index, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return cdll_get(deque->list, index, data_out);
}

ccol_status_t deque_get_node(const deque_t *deque, size_t index, dll_node_t **node_out) {
    CCOL_CHECK_INIT(deque);
    return cdll_get_node(deque->list, index, node_out);
}

ccol_status_t deque_peek(const deque_t *deque, void **data_out) {
    return deque_peek_front(deque, data_out);
}

ccol_status_t deque_peek_front(const deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return cdll_peek_front(deque->list, data_out);
}

ccol_status_t deque_peek_middle(const deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return cdll_peek_middle(deque->list, data_out);
}

ccol_status_t deque_peek_back(const deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return cdll_peek_back(deque->list, data_out);
}

dll_node_t *deque_search(const deque_t *deque, const void *data) {
    if (!deque || !deque->is_initialized || !data || !deque->list->comparator->func) return NULL;
    return cdll_search(deque->list, data);
}

// Attributes
bool deque_is_empty(const deque_t *deque) {
    if (!deque || !deque->is_initialized) return true;
    return cdll_is_empty(deque->list);
}

size_t deque_size(const deque_t *deque) {
    if (!deque || !deque->is_initialized) return 0;
    return cdll_size(deque->list);
}

bool deque_contains(const deque_t *deque, const void *data) {
    if (!deque || !deque->is_initialized || !data || !deque->list->comparator->func) return false;
    return cdll_contains(deque->list, data);
}

bool deque_contains_node(const deque_t *deque, const dll_node_t *node) {
    if (!deque || !deque->is_initialized || !node) return false;
    return cdll_contains_node(deque->list, node);
}

// Indexing
ccol_status_t deque_safe_index_of(const deque_t *deque, void *data, size_t *out_index) {
    CCOL_CHECK_INIT(deque);
    return cdll_safe_index_of(deque->list, data, out_index);
}

size_t deque_index_of(const deque_t *deque, void *data) {
    if (!deque || !deque->is_initialized || !data || !deque->list->comparator->func) return DEQUE_INDEX_NOT_FOUND;
    return cdll_index_of(deque->list, data);
}

// Utilities
ccol_status_t deque_set(deque_t *deque, size_t index, void *data) {
    CCOL_CHECK_INIT(deque);
    return cdll_set(deque->list, index, data);
}

ccol_status_t deque_swap_data(deque_t *deque, size_t i, size_t j) {
    CCOL_CHECK_INIT(deque);
    return cdll_swap_data(deque->list, i, j);
}

ccol_status_t deque_swap_nodes(deque_t *deque, dll_node_t *x, dll_node_t *y) {
    CCOL_CHECK_INIT(deque);
    return cdll_swap_nodes(deque->list, x, y);
}

ccol_status_t deque_reverse(deque_t *deque) {
    CCOL_CHECK_INIT(deque);
    return cdll_reverse(deque->list);
}

// Copy / Clone
ccol_status_t deque_deep_clone(const deque_t *src, deque_t **deque_out) {
    CCOL_CHECK_INIT(src);
    if (!deque_out) return CCOL_STATUS_INVALID_ARG;
    if (!src->list->copier.func) return CCOL_STATUS_COPY_FUNC;

    *deque_out = NULL;

    deque_t *clone = calloc(1, sizeof(deque_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    ccol_status_t status = deque_init(
        clone,
        src->list->copier,
        src->list->freer,
        src->list->printer,
        src->list->comparator
    );
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    status = cdll_clone_into(src->list, clone->list);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        *deque_out = NULL;
        return status;
    }

    *deque_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t deque_shallow_clone(const deque_t *src, deque_t **deque_out) {
    CCOL_CHECK_INIT(src);
    if (!deque_out) return CCOL_STATUS_INVALID_ARG;

    *deque_out = NULL;

    deque_t *clone = calloc(1, sizeof(deque_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    cdll_t *list_clone = NULL;
    ccol_status_t status = cdll_shallow_clone(src->list, &list_clone);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    clone->list = list_clone;
    free(list_clone);

    *deque_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t deque_clone(const deque_t *src, deque_t **deque_out) {
    return deque_deep_clone(src, deque_out);
}

ccol_status_t deque_deep_copy(deque_t *dest, const deque_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (!src->list->copier.func) return CCOL_STATUS_COPY_FUNC;
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = cdll_clear(dest->list);
    if (status != CCOL_STATUS_OK) return status;

    return cdll_deep_copy(dest->list, src->list);
}

ccol_status_t deque_shallow_copy(deque_t *dest, const deque_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (dest == src) return CCOL_STATUS_OK;

    dll_node_t *node = dest->list->head;
    for (size_t i = 0; i < dest->list->size; i++) {
        dll_node_t *next = node->next;
        free(node);
        node = next;
    }
    dest->list->head = dest->list->tail = NULL;
    dest->list->size = 0;

    dll_node_t *curr = src->list->head;
    for (size_t i = 0; i < src->list->size; i++) {
        ccol_status_t status = cdll_push_back(dest->list, curr->data);
        if (status != CCOL_STATUS_OK) {
            node = dest->list->head;
            for (size_t j = 0; j < dest->list->size; j++) {
                dll_node_t *next = node->next;
                free(node);
                node = next;
            }
            dest->list->head = dest->list->tail = NULL;
            dest->list->size = 0;
            return status;
        }
        curr = curr->next;
    }

    dest->list->copier = src->list->copier;
    dest->list->freer = src->list->freer;
    dest->list->printer = src->list->printer;
    dest->list->comparator = src->list->comparator;

    return CCOL_STATUS_OK;
}

ccol_status_t deque_copy(deque_t *dest, const deque_t *src) {
    return deque_deep_copy(dest, src);
}

// Cleanup
ccol_status_t deque_clear(deque_t *deque) {
    CCOL_CHECK_INIT(deque);
    return cdll_clear(deque->list);
}

ccol_status_t deque_destroy(deque_t *deque) {
    CCOL_CHECK_INIT(deque);

    ccol_status_t status = cdll_destroy(deque->list);
    if (status != CCOL_STATUS_OK) return status;

    return deque_uninit(deque);
}

ccol_status_t deque_free(deque_t **deque_ptr) {
    if (!deque_ptr || !*deque_ptr || !(*deque_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = deque_destroy(*deque_ptr);

    free(*deque_ptr);
    *deque_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t deque_print(const deque_t *deque) {
    CCOL_CHECK_INIT(deque);
    return cdll_print(deque->list);
}
