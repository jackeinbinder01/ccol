/*
 * ccol/queue.h
 *
 * FIFO queue
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "queue.h"
#include "ccol_macros.h"
#include "ccol_status.h"

// Create / Initialize
ccol_status_t queue_init(
    queue_t *queue,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
);

ccol_status_t queue_create(
    queue_t **queue_out,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
);

// Insertion
ccol_status_t queue_push(queue_t *queue, void *data);

// Removal
ccol_status_t queue_pop(queue_t *queue, void **data_out);

// Access
ccol_status_t queue_peek(const queue_t *queue, void **data_out);

// Attributes
bool queue_is_empty(const queue_t *queue);
size_t queue_size(const queue_t *queue);

// Copy / Clone
ccol_status_t queue_clone(const queue_t *src, queue_t **queue_out);
ccol_status_t queue_deep_clone(const queue_t *src, queue_t **queue_out);
ccol_status_t queue_shallow_clone(const queue_t *src, queue_t **queue_out);

ccol_status_t queue_copy(queue_t *dest, const queue_t *src);
ccol_status_t queue_deep_copy(queue_t *dest, const queue_t *src);
ccol_status_t queue_shallow_copy(queue_t *dest, const queue_t *src);

// Cleanup
ccol_status_t queue_clear(queue_t *queue);
ccol_status_t queue_destroy(queue_t *queue);
ccol_status_t queue_free(queue_t **queue_ptr);

// Print / Debug
ccol_status_t queue_print(const queue_t *queue);