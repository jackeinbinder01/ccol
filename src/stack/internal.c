/*
 * ccol/src/stack/internal.c
 *
 * Internal helper function implementations for stack (LIFO).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "ccol/ccol_macros.h"
#include "ccol/ccol_status.h"

#include "../stack/internal.h"
#include "../deque/internal.h"

ccol_status_t ccol__stack_uninit(ccol_stack_t *stack) {
    CCOL_CHECK_INIT(stack);

    ccol_status_t status = ccol__deque_uninit(stack->deque);
    if (status != CCOL_STATUS_OK) return status;
    free(stack->deque);
    stack->deque = NULL;

    stack->is_initialized = false;
    return CCOL_STATUS_OK;
}