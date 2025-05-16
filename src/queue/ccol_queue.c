/*
 * ccol/src/queue/ccol_queue.c
 *
 * Queue (FIFO) implementation.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ccol/ccol_queue.h"
#include "ccol/ccol_deque.h"
#include "ccol/ccol_macros.h"
#include "ccol/ccol_status.h"

#include "cdll/internal.h"
#include "internal.h"

// Create / Initialize
ccol_status_t ccol_queue_init(
    ccol_queue_t *queue,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
) {
    if (!queue) return CCOL_STATUS_INVALID_ARG;

    queue->deque = malloc(sizeof(ccol_deque_t));
    if (!queue->deque) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_deque_init(queue->deque, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(queue->deque);
        return status;
    }

    queue->is_initialized = true;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_queue_create(
    ccol_queue_t **queue_out,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
) {
    if (!queue_out) return CCOL_STATUS_INVALID_ARG;

    *queue_out = NULL;

    ccol_queue_t *queue = calloc(1, sizeof(ccol_queue_t));
    if (!queue) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_queue_init(queue, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(queue);
        return status;
    }

    *queue_out = queue;
    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t ccol_queue_push(ccol_queue_t *queue, void *data) {
    CCOL_CHECK_INIT(queue);
    return ccol_deque_push_back(queue->deque, data);
}

// Removal
ccol_status_t ccol_queue_pop(ccol_queue_t *queue, void **data_out) {
    CCOL_CHECK_INIT(queue);
    return ccol_deque_pop_front(queue->deque, data_out);
}

// Access
ccol_status_t ccol_queue_peek(const ccol_queue_t *queue, void **data_out) {
    CCOL_CHECK_INIT(queue);
    return ccol_deque_peek_front(queue->deque, data_out);
}

// Attributes
bool ccol_queue_is_empty(const ccol_queue_t *queue) {
    if (!queue || !queue->is_initialized) return true;
    return ccol_deque_is_empty(queue->deque);
}

size_t ccol_queue_size(const ccol_queue_t *queue) {
    if (!queue || !queue->is_initialized) return 0;
    return ccol_deque_size(queue->deque);
}

// Copy / Clone
ccol_status_t ccol_queue_deep_clone(const ccol_queue_t *src, ccol_queue_t **queue_out) {
    CCOL_CHECK_INIT(src);
    if (!queue_out) return CCOL_STATUS_INVALID_ARG;

    *queue_out = NULL;

    ccol_queue_t *clone = calloc(1, sizeof(ccol_queue_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_queue_init(
        clone,
        src->deque->list->copier,
        src->deque->list->freer,
        src->deque->list->printer,
        src->deque->list->comparator
    );
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    status = ccol__cdll_clone_into(src->deque->list, clone->deque->list);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    *queue_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_queue_shallow_clone(const ccol_queue_t *src, ccol_queue_t **queue_out) {
    CCOL_CHECK_INIT(src);
    if (!queue_out) return CCOL_STATUS_INVALID_ARG;

    *queue_out = NULL;

    ccol_queue_t *clone = calloc(1, sizeof(ccol_queue_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    ccol_deque_t *deque_clone = NULL;
    ccol_status_t status = ccol_deque_shallow_clone(src->deque, &deque_clone);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    clone->deque = deque_clone;

    *queue_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_queue_clone(const ccol_queue_t *src, ccol_queue_t **queue_out) {
    return ccol_queue_deep_clone(src, queue_out);
}

ccol_status_t ccol_queue_deep_copy(ccol_queue_t *dest, const ccol_queue_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = ccol_deque_clear(dest->deque);
    if (status != CCOL_STATUS_OK) {
        dest->deque->list->head = NULL;
        dest->deque->list->tail = NULL;
        dest->deque->list->size = 0;
        return status;
    }

    return ccol_deque_deep_copy(dest->deque, src->deque);
}

ccol_status_t ccol_queue_shallow_copy(ccol_queue_t *dest, const ccol_queue_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = ccol_deque_clear(dest->deque);
    if (status != CCOL_STATUS_OK) {
        dest->deque->list->head = NULL;
        dest->deque->list->tail = NULL;
        dest->deque->list->size = 0;
        return status;
    }

    return ccol_deque_shallow_copy(dest->deque, src->deque);
}

ccol_status_t ccol_queue_copy(ccol_queue_t *dest, const ccol_queue_t *src) {
    return ccol_queue_deep_copy(dest, src);
}

// Cleanup
ccol_status_t ccol_queue_clear(ccol_queue_t *queue) {
    CCOL_CHECK_INIT(queue);
    return ccol_deque_clear(queue->deque);
}

ccol_status_t ccol_queue_destroy(ccol_queue_t *queue) {
    CCOL_CHECK_INIT(queue);
    ccol_status_t status = ccol_deque_clear(queue->deque);
    if (status != CCOL_STATUS_OK) return status;

    return ccol__queue_uninit(queue);
}

ccol_status_t ccol_queue_free(ccol_queue_t **queue_ptr) {
    if (!queue_ptr || !*queue_ptr || !(*queue_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = ccol_queue_destroy(*queue_ptr);

    free(*queue_ptr);
    *queue_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t ccol_queue_print(const ccol_queue_t *queue) {
    CCOL_CHECK_INIT(queue);
    return ccol_deque_print(queue->deque);
}