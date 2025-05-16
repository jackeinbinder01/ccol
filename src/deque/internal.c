/*
 * ccol/src/deque/internal.c
 *
 * Internal helpers for deque
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>

#include "ccol/ccol_deque.h"
#include "ccol/ccol_macros.h"
#include "ccol/ccol_status.h"

#include "ccol/ccol_cdll.h"
#include "../cdll/internal.h"


ccol_status_t ccol__deque_uninit(ccol_deque_t *deque) {
    CCOL_CHECK_INIT(deque);

    ccol_status_t status = ccol__cdll_uninit(deque->list);
    if (status != CCOL_STATUS_OK) return status;
    free(deque->list);
    deque->list = NULL;

    deque->is_initialized = false;
    return CCOL_STATUS_OK;
}