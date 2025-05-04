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

    cdll->copy_func = cdll->free_func = cdll->print_func = NULL;
    cdll->cmp = cdll->ctx = NULL;

    cdll->is_initialized = false;

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_clone_into(const cdll_t *src, cdll_t *dest) {
    CCOL_CHECK_INIT(src);
    if (!dest || src == dest) return CCOL_STATUS_INVALID_ARG;

    if (dest->is_initialized) cdll_clear(dest, dest->free_func, dest->ctx);

    ccol_status_t status = cdll_init(dest, src->copy_func, src->free_func, src->print_func, src->cmp, src->ctx);
    if (status != CCOL_STATUS_OK) return status;

    dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        // Shallow clone if no copy_func is provided
        void *data_copy = src->copy_func ? src->copy_func(curr->data, src->ctx) : curr->data;
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
    return cdll_clear(dest, dest->free_func, dest->ctx);
}

void cdll_dispose_node(dll_t *cdll, dll_node_t *node) {
    if (!node) return;
    if (cdll->free_func && node->data) cdll->free_func(node->data, cdll->ctx);
    dll_free_node(node);
}
