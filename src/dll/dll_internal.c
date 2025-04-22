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

    if (node->data) free(node->data);
    node->data = node->next = node->prev = NULL;
    free(node);
}

void dll_dispose_node(dll_node_t *node, free_func_t free_data, void *ctx) {
    if (!node) return;
    if (free_data && node->data) free_data(node->data, ctx);
    dll_free_node(node);
}

dll_node_t *dll_search_bounded(const dll_node_t *head, size_t size, const void *data, comparator_t cmp, void *ctx) {
    if (!head || size == 0 || !data || !cmp) return NULL;

    dll_node_t *curr = (dll_node_t *)head;
    for (size_t i = 0; i < size; i++) {
        if (cmp(curr->data, data, ctx) == 0) return curr;
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
void dll_uninit(dll_t *dll) {
    if (!dll || !dll->is_initialized) return;

    dll->head = dll->tail = NULL;
    dll->size = 0;
    dll->is_initialized = false;
}

ccol_status_t dll_clone_into(const dll_t *src, dll_t *dest, copy_func_t copy_data, void *ctx) {
    CCOL_CHECK_INIT(src);
    if (!dest || !copy_data || src == dest) return CCOL_STATUS_INVALID_ARG;

    if (dest->is_initialized) dll_clear(dest, NULL, ctx);

    ccol_status_t status = dll_init(dest);
    if (status != CCOL_STATUS_OK) return status;

    dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        void *data_copy = copy_data(curr->data, ctx);
        status = dll_push_back(dest, data_copy);
        if (status != CCOL_STATUS_OK) {
            dll_clone_rollback(dest, NULL, ctx);
            return status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t dll_deep_clone_into(const dll_t *src, dll_t *dest, void *ctx) {
    return dll_clone_into(src, dest, COPY_DEFAULT, ctx);
}

void dll_clone_rollback(dll_t *dest, free_func_t free_data, void *ctx) {
    dll_clear(dest, free_data, ctx);
}
