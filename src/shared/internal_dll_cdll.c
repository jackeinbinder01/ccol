/*
 * ccol/src/shared/internal_dll_cdll.c
 *
 * Internal function helper implementations for dll (shared with cdll).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>

#include "ccol/ccol_status.h"
#include "internal_dll_cdll.h"

void ccol__dll_node_free(ccol_dll_node_t *node) {
    free(node);
}

ccol_dll_node_t *ccol__dll_node_get_middle(const ccol_dll_node_t *head, size_t size) {
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

ccol_status_t ccol__dll_node_get_bounded(
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