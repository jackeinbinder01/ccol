/*
 * ccol/src/stack/internal.h
 *
 * Internal helper functions for stack (LIFO).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_STACK_INTERNAL_H
#define CCOL_STACK_INTERNAL_H

#include "ccol/ccol_stack.h"

ccol_status_t ccol__stack_uninit(ccol_stack_t *stack);

#endif  // CCOL_STACK_INTERNAL_H
