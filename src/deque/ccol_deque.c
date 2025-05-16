/*
 * ccol/src/deque/ccol_deque.h
 *
 * Double-ended queue (deque) implemention.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ccol/ccol_deque.h"
#include "ccol/ccol_status.h"
#include "ccol/ccol_macros.h"
#include "ccol/ccol_constants.h"

#include "internal.h"

#include "ccol/ccol_cdll.h"
#include "ccol/ccol_dll.h"

// Create / Initialize
ccol_status_t ccol_deque_init(
    ccol_deque_t *deque,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
) {
    if (!deque) return CCOL_STATUS_INVALID_ARG;

    deque->list = malloc(sizeof(ccol_cdll_t));
    if (!deque->list) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_cdll_init(deque->list, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(deque->list);
        return status;
    }

    deque->is_initialized = true;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_deque_create(
    ccol_deque_t **deque_out,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
) {
    if (!deque_out) return CCOL_STATUS_INVALID_ARG;

    *deque_out = NULL;

    ccol_deque_t *deque = calloc(1, sizeof(ccol_deque_t));
    if (!deque) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_deque_init(deque, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(deque);
        return status;
    }

    *deque_out = deque;
    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t ccol_deque_push(ccol_deque_t *deque, void *data) {
    return ccol_deque_push_back(deque, data);
}

ccol_status_t ccol_deque_push_front(ccol_deque_t *deque, void *data) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_push_front(deque->list, data);
}

ccol_status_t ccol_deque_push_middle(ccol_deque_t *deque, void *data) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_push_middle(deque->list, data);
}

ccol_status_t ccol_deque_push_back(ccol_deque_t *deque, void *data) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_push_back(deque->list, data);
}

ccol_status_t ccol_deque_insert_before(ccol_deque_t *deque, ccol_dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_insert_before(deque->list, ref_node, data);
}

ccol_status_t ccol_deque_insert_after(ccol_deque_t *deque, ccol_dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_insert_after(deque->list, ref_node, data);
}

// Removal
ccol_status_t ccol_deque_pop(ccol_deque_t *deque, void **data_out) {
    return ccol_deque_pop_front(deque, data_out);
}

ccol_status_t ccol_deque_pop_front(ccol_deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_pop_front(deque->list, data_out);
}

ccol_status_t ccol_deque_pop_middle(ccol_deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_pop_middle(deque->list, data_out);
}

ccol_status_t ccol_deque_pop_back(ccol_deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_pop_back(deque->list, data_out);
}

ccol_status_t ccol_deque_remove_node(ccol_deque_t *deque, ccol_dll_node_t* node) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_remove_node(deque->list, node);
}

ccol_status_t ccol_deque_remove(ccol_deque_t *deque, void *data) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_remove(deque->list, data);
}

// Access
ccol_status_t ccol_deque_get(const ccol_deque_t *deque, size_t index, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_get(deque->list, index, data_out);
}

ccol_status_t ccol_deque_get_node(const ccol_deque_t *deque, size_t index, ccol_dll_node_t **node_out) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_get_node(deque->list, index, node_out);
}

ccol_status_t ccol_deque_peek(const ccol_deque_t *deque, void **data_out) {
    return ccol_deque_peek_front(deque, data_out);
}

ccol_status_t ccol_deque_peek_front(const ccol_deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_peek_front(deque->list, data_out);
}

ccol_status_t ccol_deque_peek_middle(const ccol_deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_peek_middle(deque->list, data_out);
}

ccol_status_t ccol_deque_peek_back(const ccol_deque_t *deque, void **data_out) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_peek_back(deque->list, data_out);
}

ccol_dll_node_t *ccol_deque_search(const ccol_deque_t *deque, const void *data) {
    if (!deque || !deque->is_initialized || !data || !deque->list->comparator->func) return NULL;
    return ccol_cdll_search(deque->list, data);
}

// Attributes
bool ccol_deque_is_empty(const ccol_deque_t *deque) {
    if (!deque || !deque->is_initialized) return true;
    return ccol_cdll_is_empty(deque->list);
}

size_t ccol_deque_size(const ccol_deque_t *deque) {
    if (!deque || !deque->is_initialized) return 0;
    return ccol_cdll_size(deque->list);
}

bool ccol_deque_contains(const ccol_deque_t *deque, const void *data) {
    if (!deque || !deque->is_initialized || !data || !deque->list->comparator->func) return false;
    return ccol_cdll_contains(deque->list, data);
}

bool ccol_deque_contains_node(const ccol_deque_t *deque, const ccol_dll_node_t *node) {
    if (!deque || !deque->is_initialized || !node) return false;
    return ccol_cdll_contains_node(deque->list, node);
}

// Indexing
ccol_status_t ccol_deque_safe_index_of(const ccol_deque_t *deque, void *data, size_t *out_index) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_safe_index_of(deque->list, data, out_index);
}

size_t ccol_deque_index_of(const ccol_deque_t *deque, void *data) {
    if (!deque || !deque->is_initialized || !data || !deque->list->comparator->func) return CCOL_DEQUE_INDEX_NOT_FOUND;
    return ccol_cdll_index_of(deque->list, data);
}

// Utilities
ccol_status_t ccol_deque_set(ccol_deque_t *deque, size_t index, void *data) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_set(deque->list, index, data);
}

ccol_status_t ccol_deque_swap_data(ccol_deque_t *deque, size_t i, size_t j) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_swap_data(deque->list, i, j);
}

ccol_status_t ccol_deque_swap_nodes(ccol_deque_t *deque, ccol_dll_node_t *x, ccol_dll_node_t *y) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_swap_nodes(deque->list, x, y);
}

ccol_status_t ccol_deque_reverse(ccol_deque_t *deque) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_reverse(deque->list);
}

// Copy / Clone
ccol_status_t ccol_deque_deep_clone(const ccol_deque_t *src, ccol_deque_t **deque_out) {
    CCOL_CHECK_INIT(src);
    if (!deque_out) return CCOL_STATUS_INVALID_ARG;
    if (!src->list->copier.func) return CCOL_STATUS_COPY_FUNC;

    *deque_out = NULL;

    ccol_deque_t *clone = calloc(1, sizeof(ccol_deque_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_deque_init(
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

    status = ccol__cdll_clone_into(src->list, clone->list);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        *deque_out = NULL;
        return status;
    }

    *deque_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_deque_shallow_clone(const ccol_deque_t *src, ccol_deque_t **deque_out) {
    CCOL_CHECK_INIT(src);
    if (!deque_out) return CCOL_STATUS_INVALID_ARG;

    *deque_out = NULL;

    ccol_deque_t *clone = calloc(1, sizeof(ccol_deque_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    ccol_cdll_t *list_clone = NULL;
    ccol_status_t status = ccol_cdll_shallow_clone(src->list, &list_clone);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    clone->list = list_clone;
    free(list_clone);

    *deque_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_deque_clone(const ccol_deque_t *src, ccol_deque_t **deque_out) {
    return ccol_deque_deep_clone(src, deque_out);
}

ccol_status_t ccol_deque_deep_copy(ccol_deque_t *dest, const ccol_deque_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (!src->list->copier.func) return CCOL_STATUS_COPY_FUNC;
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = ccol_cdll_clear(dest->list);
    if (status != CCOL_STATUS_OK) return status;

    return ccol_cdll_deep_copy(dest->list, src->list);
}

ccol_status_t ccol_deque_shallow_copy(ccol_deque_t *dest, const ccol_deque_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (dest == src) return CCOL_STATUS_OK;

    ccol_dll_node_t *node = dest->list->head;
    for (size_t i = 0; i < dest->list->size; i++) {
        ccol_dll_node_t *next = node->next;
        free(node);
        node = next;
    }
    dest->list->head = dest->list->tail = NULL;
    dest->list->size = 0;

    ccol_dll_node_t *curr = src->list->head;
    for (size_t i = 0; i < src->list->size; i++) {
        ccol_status_t status = ccol_cdll_push_back(dest->list, curr->data);
        if (status != CCOL_STATUS_OK) {
            node = dest->list->head;
            for (size_t j = 0; j < dest->list->size; j++) {
                ccol_dll_node_t *next = node->next;
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

ccol_status_t ccol_deque_copy(ccol_deque_t *dest, const ccol_deque_t *src) {
    return ccol_deque_deep_copy(dest, src);
}

// Cleanup
ccol_status_t ccol_deque_clear(ccol_deque_t *deque) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_clear(deque->list);
}

ccol_status_t ccol_deque_destroy(ccol_deque_t *deque) {
    CCOL_CHECK_INIT(deque);

    ccol_status_t status = ccol_cdll_destroy(deque->list);
    if (status != CCOL_STATUS_OK) return status;

    return ccol__deque_uninit(deque);
}

ccol_status_t ccol_deque_free(ccol_deque_t **deque_ptr) {
    if (!deque_ptr || !*deque_ptr || !(*deque_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = ccol_deque_destroy(*deque_ptr);

    free(*deque_ptr);
    *deque_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t ccol_deque_print(const ccol_deque_t *deque) {
    CCOL_CHECK_INIT(deque);
    return ccol_cdll_print(deque->list);
}
