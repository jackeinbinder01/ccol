/*
 * ccol/deque_internal.c
 *
 * Internal helpers for deque
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "cdll.h"
#include "cdll_internal.h"
#include "deque.h"
#include "ccol_macros.h"
#include "ccol_status.h"

ccol_status_t deque_uninit(deque_t *deque) {
    CCOL_CHECK_INIT(deque);

    cdll_uninit(deque->list);
    deque->is_initialized = false;

    return CCOL_STATUS_OK;
}