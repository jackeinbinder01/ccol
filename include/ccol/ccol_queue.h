/*
 * ccol/ccol_queue.h
 *
 * Queue (FIFO) API.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_QUEUE_H
#define CCOL_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

#include "ccol_constants.h"
#include "ccol_status.h"
#include "ccol_deque.h"

typedef struct ccol_queue {
    ccol_deque_t *deque;
    bool is_initialized;
} ccol_queue_t;

// Create / Initialize
ccol_status_t ccol_queue_init(
    ccol_queue_t *queue,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

ccol_status_t ccol_queue_create(
    ccol_queue_t **queue_out,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

// Insertion
ccol_status_t ccol_queue_push(ccol_queue_t *queue, void *data);

// Removal
ccol_status_t ccol_queue_pop(ccol_queue_t *queue, void **data_out);

// Access
ccol_status_t ccol_queue_peek(const ccol_queue_t *queue, void **data_out);

// Attributes
bool ccol_queue_is_empty(const ccol_queue_t *queue);
size_t ccol_queue_size(const ccol_queue_t *queue);

// Copy / Clone
ccol_status_t ccol_queue_clone(const ccol_queue_t *src, ccol_queue_t **queue_out);
ccol_status_t ccol_queue_deep_clone(const ccol_queue_t *src, ccol_queue_t **queue_out);
ccol_status_t ccol_queue_shallow_clone(const ccol_queue_t *src, ccol_queue_t **queue_out);

ccol_status_t ccol_queue_copy(ccol_queue_t *dest, const ccol_queue_t *src);
ccol_status_t ccol_queue_deep_copy(ccol_queue_t *dest, const ccol_queue_t *src);
ccol_status_t ccol_queue_shallow_copy(ccol_queue_t *dest, const ccol_queue_t *src);

// Cleanup
ccol_status_t ccol_queue_clear(ccol_queue_t *queue);
ccol_status_t ccol_queue_destroy(ccol_queue_t *queue);
ccol_status_t ccol_queue_free(ccol_queue_t **queue_ptr);

// Print / Debug
ccol_status_t ccol_queue_print(const ccol_queue_t *queue);

#endif  // CCOL_QUEUE_H
