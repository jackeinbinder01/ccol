/*
 * ccol/src/iterator/ccol_stack_iterator.c
 *
 * Iterator implementation for stack (LIFO).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdbool.h>

#include "ccol/ccol_stack.h"
#include "ccol/ccol_stack_iterator.h"
#include "ccol/ccol_iterator.h"

// Private
static bool ccol_stack_has_next(ccol_iterator_t *iter) {
    if (!iter || !iter->state) return false;
    ccol_stack_iterator_state_t *state = iter->state;
    return state->step < state->stack->deque.list.size;
}

static void *ccol_stack_next(ccol_iterator_t *iter) {
    if (!iter || !iter->state) return NULL;
    ccol_stack_iterator_state_t *state = iter->state;

    if (!state->current || state->step >= state->stack->deque.list.size) return NULL;

    void *data = state->current->data;
    state->current = state->current->prev;
    state->step++;
    return data;
}

static void ccol_stack_iterator_destroy(ccol_iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create
ccol_iterator_t *ccol_stack_iterator_create(const ccol_stack_t *stack) {
    if (!stack || !stack->is_initialized) return NULL;

    ccol_stack_iterator_state_t *state = calloc(1, sizeof(ccol_stack_iterator_state_t));
    if (!state) return NULL;

    ccol_iterator_t *iter = calloc(1, sizeof(ccol_iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->stack = stack;
    state->current = stack->deque.list.tail;

    iter->container = (void *)stack;
    iter->state = state;
    iter->has_next = ccol_stack_has_next;
    iter->next = ccol_stack_next;
    iter->destroy = ccol_stack_iterator_destroy;

    return iter;
}