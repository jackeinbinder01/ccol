/*
 * ccol/src/dll/internal.c
 *
 * Internal helpers for doubly-linked list (dll).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ccol/ccol_dll.h"
#include "ccol/ccol_status.h"
#include "ccol/ccol_macros.h"

#include "internal.h"
#include "internal_dll_cdll.h"

void ccol__dll_dispose_node(ccol_dll_t *dll, ccol_dll_node_t *node) {
    if (!node) return;
    if (dll->freer.func && node->data) dll->freer.func(node->data, dll->freer.ctx);
    ccol__dll_node_free(node);
}

ccol_dll_node_t *ccol__dll_search_bounded(
    const ccol_dll_t *dll,
    const ccol_dll_node_t *head,
    size_t size, const void *data
) {
    if (!dll || !head || size == 0 || !data || !dll->comparator.func) return NULL;

    ccol_dll_node_t *curr = (ccol_dll_node_t *)head;
    for (size_t i = 0; i < size; i++) {
        if (dll->comparator.func(curr->data, data, dll->comparator.ctx) == 0) return curr;
        curr = curr->next;
    }

    return NULL;
}

ccol_status_t ccol__dll_uninit(ccol_dll_t *dll) {
    CCOL_CHECK_INIT(dll);

    dll->head = dll->tail = NULL;
    dll->size = 0;

    dll->copier = (ccol_copy_t){0};
    dll->freer = (ccol_free_t){0};
    dll->printer = (ccol_print_t){0};
    dll->comparator = (ccol_comparator_t){0};

    dll->is_initialized = false;

    return CCOL_STATUS_OK;
}

ccol_status_t ccol__dll_clone_rollback(ccol_dll_t *dest) {
    CCOL_CHECK_INIT(dest);
    return ccol_dll_clear(dest);
}

ccol_status_t ccol__dll_clone_into(const ccol_dll_t *src, ccol_dll_t *dest) {
    CCOL_CHECK_INIT(src);
    if (!dest || src == dest) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status;
    if (dest->is_initialized) {
         status = ccol_dll_clear(dest);
         if (status != CCOL_STATUS_OK) return status;
    }

    status = ccol_dll_init(dest, src->copier, src->freer, src->printer, src->comparator);
    if (status != CCOL_STATUS_OK) return status;

    ccol_dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        // Shallow clone if no copy_func is provided
        void *data_copy = src->copier.func ? src->copier.func(curr->data, src->copier.ctx) : curr->data;
        status = ccol_dll_push_back(dest, data_copy);
        if (status != CCOL_STATUS_OK) {
            ccol_status_t rollback_status = ccol__dll_clone_rollback(dest);
            return rollback_status != CCOL_STATUS_OK ? rollback_status : status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t ccol__dll_deep_clone_into(const ccol_dll_t *src, ccol_dll_t *dest) {
    return ccol__dll_clone_into(src, dest);
}
