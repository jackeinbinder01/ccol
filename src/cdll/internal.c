/*
 * ccol/src/cdll/internal.c
 *
 * Internal helper function implementations for circular doubly-linked list (cdll).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdbool.h>

#include "ccol/ccol_cdll.h"
#include "ccol/ccol_status.h"
#include "ccol/ccol_macros.h"

#include "internal.h"

ccol_status_t ccol__cdll_uninit(ccol_cdll_t *cdll) {
    CCOL_CHECK_INIT(cdll);

    cdll->head = cdll->tail = NULL;
    cdll->size = 0;

    cdll->copier = (ccol_copy_t){0};
    cdll->freer = (ccol_free_t){0};
    cdll->printer = (ccol_print_t){0};
    cdll->comparator = (ccol_comparator_t){0};

    cdll->is_initialized = false;

    return CCOL_STATUS_OK;
}

ccol_status_t ccol__cdll_clone_into(const ccol_cdll_t *src, ccol_cdll_t *dest) {
    CCOL_CHECK_INIT(src);
    if (!dest || src == dest) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status;
    if (dest->is_initialized) {
        status = ccol_cdll_clear(dest);
        if (status != CCOL_STATUS_OK) return status;
    }

    status = ccol_cdll_init(dest, src->copier, src->freer, src->printer, src->comparator);
    if (status != CCOL_STATUS_OK) return status;

    ccol_dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        // Shallow clone if no copy_func is provided
        void *data_copy = src->copier.func ? src->copier.func(curr->data, src->copier.ctx) : curr->data;
        status = ccol_cdll_push_back(dest, data_copy);
        if (status != CCOL_STATUS_OK) {
            ccol_status_t rollback_status = ccol__cdll_clone_rollback (dest);
            return rollback_status != CCOL_STATUS_OK ? rollback_status : status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t ccol__cdll_deep_clone_into(const ccol_cdll_t *src, ccol_cdll_t *dest) {
    return ccol__cdll_clone_into(src, dest);
}

ccol_status_t ccol__cdll_clone_rollback (ccol_cdll_t *dest) {
    CCOL_CHECK_INIT(dest);
    return ccol_cdll_clear(dest);
}

void ccol__cdll_dispose_node(ccol_cdll_t *cdll, ccol_dll_node_t *node) {
    if (!node) return;
    if (cdll->freer.func && node->data) cdll->freer.func(node->data, cdll->freer.ctx);
    ccol__dll_free_node(node);
}

ccol_dll_node_t *ccol__cdll_search_bounded(
    const ccol_cdll_t *cdll,
    const ccol_dll_node_t *head,
    size_t size,
    const void *data
) {
    if (!cdll || !head || size == 0 || !data || !cdll->comparator.func) return NULL;

    ccol_dll_node_t *curr = (ccol_dll_node_t *)head;
    for (size_t i = 0; i < size; i++) {
        if (cdll->comparator.func(curr->data, data, cdll->comparator.ctx) == 0) return curr;
        curr = curr->next;
    }

    return NULL;
}
