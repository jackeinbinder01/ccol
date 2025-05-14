/*
 * ccol/queue_internal.h
 *
 * Internal helpers for queue
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "queue_internal.h"
#include "deque_internal.h"
#include "ccol_macros.h"
#include "ccol_status.h"

ccol_status_t queue_uninit(queue_t *queue) {
    CCOL_CHECK_INIT(queue);

    ccol_status_t status = deque_uninit(queue->deque);
    if (status != CCOL_STATUS_OK) return status;
    free(queue->deque);
    queue->deque = NULL;

    queue->is_initialized = false;
    return CCOL_STATUS_OK;
}