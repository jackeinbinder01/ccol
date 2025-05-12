/*
 * ccol/cdll_internal.c
 *
 * Internal helpers for cdll
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdbool.h>

#include "cdll.h"
#include "cdll_internal.h"
#include "ccol_status.h"
#include "ccol_macros.h"

ccol_status_t cdll_uninit(cdll_t *cdll) {
    CCOL_CHECK_INIT(cdll);

    cdll->head = cdll->tail = NULL;
    cdll->size = 0;

    cdll->copier = (copy_t){0};
    cdll->freer = (free_t){0};
    cdll->printer = (print_t){0};
    cdll->comparator = (comparator_t){0};

    cdll->is_initialized = false;

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_clone_into(const cdll_t *src, cdll_t *dest) {
    CCOL_CHECK_INIT(src);
    if (!dest || src == dest) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status;
    if (dest->is_initialized) {
        status = cdll_clear(dest);
        if (status != CCOL_STATUS_OK) return status;
    }

    status = cdll_init(dest, src->copier, src->freer, src->printer, src->comparator);
    if (status != CCOL_STATUS_OK) return status;

    dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        // Shallow clone if no copy_func is provided
        void *data_copy = src->copier.func ? src->copier.func(curr->data, src->copier.ctx) : curr->data;
        status = cdll_push_back(dest, data_copy);
        if (status != CCOL_STATUS_OK) {
            ccol_status_t rollback_status = cdll_clone_rollback(dest);
            return rollback_status != CCOL_STATUS_OK ? rollback_status : status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_deep_clone_into(const cdll_t *src, cdll_t *dest) {
    return cdll_clone_into(src, dest);
}

ccol_status_t cdll_clone_rollback(cdll_t *dest) {
    CCOL_CHECK_INIT(dest);
    return cdll_clear(dest);
}

void cdll_dispose_node(cdll_t *cdll, dll_node_t *node) {
    if (!node) return;
    if (cdll->freer.func && node->data) cdll->freer.func(node->data, cdll->freer.ctx);
    dll_free_node(node);
}

dll_node_t *cdll_search_bounded(const cdll_t *cdll, const dll_node_t *head, size_t size, const void *data) {
    if (!cdll || !head || size == 0 || !data || !cdll->comparator.func) return NULL;

    dll_node_t *curr = (dll_node_t *)head;
    for (size_t i = 0; i < size; i++) {
        if (cdll->comparator.func(curr->data, data, cdll->comparator.ctx) == 0) return curr;
        curr = curr->next;
    }

    return NULL;
}
