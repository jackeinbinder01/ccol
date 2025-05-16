/*
 * ccol/stack_internal.h
 *
 * Internal helpers for stack
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "stack_internal.h"
#include "deque_internal.h"
#include "ccol_macros.h"
#include "ccol_status.h"

ccol_status_t stack_uninit(stack_t *stack) {
    CCOL_CHECK_INIT(stack);

    ccol_status_t status = deque_uninit(stack->deque);
    if (status != CCOL_STATUS_OK) return status;
    free(stack->deque);
    stack->deque = NULL;

    stack->is_initialized = false;
    return CCOL_STATUS_OK;
}