/*
 * ccol/dll_internal.c
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

// DLL & CDLL
dll_node_t *dll_get_middle_node(const dll_node_t *head, size_t size) {
    if (!head || size == 0) return NULL;

    const dll_node_t *slow = head, *fast = head;

    size_t steps = 0;
    while (fast && fast->next && steps + 2 <= size) {
        slow = slow->next;
        fast = fast->next->next;
        steps += 2;
    }

    return (dll_node_t *)slow;
}

void dll_free_node(dll_node_t *node) {
    if (!node) return;

    node->data = node->next = node->prev = NULL;
    free(node);
}

void dll_dispose_node(dll_t *dll, dll_node_t *node) {
    if (!node) return;
    if (dll->free_func && node->data) dll->free_func(node->data, dll->ctx);
    dll_free_node(node);
}

dll_node_t *dll_search_bounded(const dll_t *dll, const dll_node_t *head, size_t size, const void *data) {
    if (!head || size == 0 || !data) return NULL;

    dll_node_t *curr = (dll_node_t *)head;
    for (size_t i = 0; i < size; i++) {
        if (dll->cmp(curr->data, data, dll->ctx) == 0) return curr;
        curr = curr->next;
    }

    return NULL;
}

ccol_status_t dll_get_node_bounded(const dll_node_t *head, const dll_node_t *tail, size_t size, size_t index, dll_node_t **node_out) {
    if (!head || !tail || !node_out) return CCOL_STATUS_INVALID_ARG;
    if (size == 0) return CCOL_STATUS_EMPTY;
    if (index > size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;

    dll_node_t* target;
    if (index < size / 2) {
        target = (dll_node_t *)head;
        for (size_t i = 0; i < index; i++) {
            target = target->next;
        }
    } else {
        target = (dll_node_t *)tail;
        for (size_t i = size - 1; i != index; i--) {
            target = target->prev;
        }
    }
    *node_out = target;

    return CCOL_STATUS_OK;
}

// DLL specific
ccol_status_t dll_uninit(dll_t *dll) {
    CCOL_CHECK_INIT(dll);

    dll->head = dll->tail = NULL;
    dll->size = 0;

    dll->copy_func = dll->free_func = dll->print_func = NULL;
    dll->cmp = dll->ctx = NULL;

    dll->is_initialized = false;

    return CCOL_STATUS_OK;
}

ccol_status_t dll_clone_into(const dll_t *src, dll_t *dest) {
    CCOL_CHECK_INIT(src);
    if (!dest || src == dest) return CCOL_STATUS_INVALID_ARG;

    if (dest->is_initialized) dll_clear(dest, dest->free_func, dest->ctx);

    ccol_status_t status = dll_init(dest, src->copy_func, src->free_func, src->print_func, src->cmp, src->ctx);
    if (status != CCOL_STATUS_OK) return status;

    dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        // Shallow clone if no copy_func is provided
        void *data_copy = src->copy_func ? src->copy_func(curr->data, src->ctx) : curr->data;
        status = dll_push_back(dest, data_copy);
        if (status != CCOL_STATUS_OK) {
            ccol_status_t rollback_status = dll_clone_rollback(dest);
            return rollback_status != CCOL_STATUS_OK ? rollback_status : status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t dll_deep_clone_into(const dll_t *src, dll_t *dest) {
    return dll_clone_into(src, dest);
}

ccol_status_t dll_clone_rollback(dll_t *dest) {
    CCOL_CHECK_INIT(dest);
    return dll_clear(dest, dest->free_func, dest->ctx);
}
