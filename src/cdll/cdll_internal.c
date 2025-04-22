/*
 * ccol/cdll_internal.c
 *
 * Internal helpers for cdll
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "cdll.h"
#include "cdll_internal.h"
#include "ccol_status.h"
#include "ccol_macros.h"

void cdll_uninit(cdll_t *cdll) {
    if (!cdll || !cdll->is_initialized) return;

    cdll->head = cdll->tail = NULL;
    cdll->size = 0;
    cdll->is_initialized = false;
}

ccol_status_t cdll_clone_into(const cdll_t *src, cdll_t *dest, copy_func_t copy_data, void *ctx) {
    CCOL_CHECK_INIT(src);
    if (!dest || !copy_data || src == dest) return CCOL_STATUS_INVALID_ARG;

    if (dest->is_initialized) cdll_clear(dest, NULL, ctx);

    ccol_status_t status = cdll_init(dest);
    if (status != CCOL_STATUS_OK) return status;

    dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        void *data_copy = copy_data(curr->data, ctx);
        status = cdll_push_back(dest, data_copy);
        if (status != CCOL_STATUS_OK) {
            cdll_clone_rollback(dest, NULL, ctx);
            return status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_deep_clone_into(const cdll_t *src, cdll_t *dest, void *ctx) {
    return cdll_clone_into(src, dest, COPY_DEFAULT, ctx);
}

void cdll_clone_rollback(cdll_t *dest, free_func_t free_data, void *ctx) {
    cdll_clear(dest, free_data, ctx);
}
