/*
 * ccol/queue.h
 *
 * FIFO queue
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "queue.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "deque.h"
#include "cdll_internal.h"
#include "ccol_macros.h"
#include "ccol_status.h"

// Create / Initialize
ccol_status_t queue_init(
    queue_t *queue,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
) {
    if (!queue) return CCOL_STATUS_INVALID_ARG;

    queue->deque = malloc(sizeof(deque_t));
    if (!queue->deque) return CCOL_STATUS_ALLOC;

    ccol_status_t status = deque_init(queue->deque, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(queue->deque);
        return status;
    }

    queue->is_initialized = true;
    return CCOL_STATUS_OK;
}

ccol_status_t queue_create(
    queue_t **queue_out,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
) {
    if (!queue_out) return CCOL_STATUS_INVALID_ARG;

    *queue_out = NULL;

    queue_t *queue = calloc(1, sizeof(queue_t));
    if (!queue) return CCOL_STATUS_ALLOC;

    ccol_status_t status = queue_init(queue, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(queue);
        return status;
    }

    *queue_out = queue;
    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t queue_push(queue_t *queue, void *data) {
    CCOL_CHECK_INIT(queue);
    return deque_push_back(queue->deque, data);
}

// Removal
ccol_status_t queue_pop(queue_t *queue, void **data_out) {
    CCOL_CHECK_INIT(queue);
    return deque_pop_front(queue->deque, data_out);
}

// Access
ccol_status_t queue_peek(const queue_t *queue, void **data_out) {
    CCOL_CHECK_INIT(queue);
    return deque_peek_front(queue->deque, data_out);
}

// Attributes
bool queue_is_empty(const queue_t *queue) {
    if (!queue || !queue->is_initialized) return true;
    return deque_is_empty(queue->deque);
}

size_t queue_size(const queue_t *queue) {
    if (!queue || !queue->is_initialized) return 0;
    return deque_size(queue->deque);
}

// Copy / Clone
ccol_status_t queue_deep_clone(const queue_t *src, queue_t **queue_out) {
    CCOL_CHECK_INIT(src);
    if (!queue_out) return CCOL_STATUS_INVALID_ARG;

    *queue_out = NULL;

    queue_t *clone = calloc(1, sizeof(queue_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    ccol_status_t status = queue_init(
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


    status = cdll_clone_into(src->deque->list, clone->deque->list);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    *queue_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t queue_shallow_clone(const queue_t *src, queue_t **queue_out) {
    CCOL_CHECK_INIT(src);
    if (!queue_out) return CCOL_STATUS_INVALID_ARG;

    *queue_out = NULL;

    queue_t *clone = calloc(1, sizeof(queue_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    deque_t *deque_clone = NULL;
    ccol_status_t status = deque_shallow_clone(src->deque, &deque_clone);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    clone->deque = deque_clone;

    *queue_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t queue_clone(const queue_t *src, queue_t **queue_out) {
    return queue_deep_clone(src, queue_out);
}

ccol_status_t queue_deep_copy(queue_t *dest, const queue_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = deque_clear(dest->deque);
    if (status != CCOL_STATUS_OK) {
        dest->deque->list->head = NULL;
        dest->deque->list->tail = NULL;
        dest->deque->list->size = 0;
        return status;
    }

    return deque_deep_copy(dest->deque, src->deque);
}

ccol_status_t queue_shallow_copy(queue_t *dest, const queue_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = deque_clear(dest->deque);
    if (status != CCOL_STATUS_OK) {
        dest->deque->list->head = NULL;
        dest->deque->list->tail = NULL;
        dest->deque->list->size = 0;
        return status;
    }

    return deque_shallow_copy(dest->deque, src->deque);
}

ccol_status_t queue_copy(queue_t *dest, const queue_t *src) {
    return queue_deep_copy(dest, src);
}

// Cleanup
ccol_status_t queue_clear(queue_t *queue) {
    CCOL_CHECK_INIT(queue);
    return deque_clear(queue->deque);
}

ccol_status_t queue_destroy(queue_t *queue) {
    CCOL_CHECK_INIT(queue);
    ccol_status_t status = deque_clear(queue->deque);
    if (status != CCOL_STATUS_OK) return status;

    return queue_uninit(queue);
}

ccol_status_t queue_free(queue_t **queue_ptr) {
    if (!queue_ptr || !*queue_ptr || !(*queue_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = queue_destroy(*queue_ptr);

    free(*queue_ptr);
    *queue_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t queue_print(const queue_t *queue) {
    CCOL_CHECK_INIT(queue);
    return deque_print(queue->deque);
}