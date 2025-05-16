/*
 * ccol/src/queue/internal.c
 *
 * Internal helper function implementations for queue (FIFO).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>

#include "ccol/ccol_macros.h"
#include "ccol/ccol_status.h"

#include "internal.h"
#include "deque/internal.h"

ccol_status_t ccol__queue_uninit(ccol_queue_t *queue) {
    CCOL_CHECK_INIT(queue);

    ccol_status_t status = ccol__deque_uninit(queue->deque);
    if (status != CCOL_STATUS_OK) return status;
    free(queue->deque);
    queue->deque = NULL;

    queue->is_initialized = false;
    return CCOL_STATUS_OK;
}