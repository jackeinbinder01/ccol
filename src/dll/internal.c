/*
 * ccol/src/dll/internal.c
 *
 * Internal helpers for dll
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dll.h"
#include "dll_internal.h"
#include "ccol_status.h"
#include "ccol_macros.h"

// dll & cdll
ccol_dll_node_t *ccol__dll_get_middle_node(const ccol_dll_node_t *head, size_t size) {
    if (!head || size == 0) return NULL;

    const ccol_dll_node_t *slow = head, *fast = head;

    size_t steps = 0;
    while (fast && fast->next && steps + 2 <= size) {
        slow = slow->next;
        fast = fast->next->next;
        steps += 2;
    }

    return (ccol_dll_node_t *)slow;
}

void ccol__dll_dispose_node(ccol_dll_node_t *node) {
    if (!node) return;

    node->data = node->next = node->prev = NULL;
    free(node);
}

void ccol__dll_dispose_node(ccol_dll_t *dll, ccol_dll_node_t *node) {
    if (!node) return;
    if (dll->freer.func && node->data) dll->freer.func(node->data, dll->freer.ctx);
    dll_free_node(node);
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

ccol_status_t ccol__dll_get_node_bounded(
    const ccol_dll_node_t *head,
    const ccol_dll_node_t *tail,
    size_t size, size_t index,
    ccol_dll_node_t **node_out
) {
    if (!head || !tail || !node_out) return CCOL_STATUS_INVALID_ARG;
    if (size == 0) return CCOL_STATUS_EMPTY;
    if (index > size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;

    ccol_dll_node_t* target;
    if (index < size / 2) {
        target = (ccol_dll_node_t *)head;
        for (size_t i = 0; i < index; i++) {
            target = target->next;
        }
    } else {
        target = (ccol_dll_node_t *)tail;
        for (size_t i = size - 1; i != index; i--) {
            target = target->prev;
        }
    }
    *node_out = target;

    return CCOL_STATUS_OK;
}

// dll specific
ccol_status_t ccol__dll_uninit(ccol_dll_t *dll) {
    CCOL_CHECK_INIT(dll);

    dll->head = dll->tail = NULL;
    dll->size = 0;

    dll->copier = (copy_t){0};
    dll->freer = (free_t){0};
    dll->printer = (print_t){0};
    dll->comparator = (comparator_t){0};

    dll->is_initialized = false;

    return CCOL_STATUS_OK;
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
            ccol_status_t rollback_status = dll_clone_rollback(dest);
            return rollback_status != CCOL_STATUS_OK ? rollback_status : status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t ccol__dll_deep_clone_into(const ccol_dll_t *src, ccol_dll_t *dest) {
    return dll_clone_into(src, dest);
}

ccol_status_t ccol__dll_clone_rollback(ccol_dll_t *dest) {
    CCOL_CHECK_INIT(dest);
    return dll_clear(dest);
}
