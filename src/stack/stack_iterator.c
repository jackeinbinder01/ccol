/*
 * ccol/stack_iterator.h
 *
 * Iterator functions for stack
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"
#include "stack_iterator.h"
#include "iterator.h"

// Private
static bool stack_has_next(iterator_t *iter) {
    if (!iter || !iter->state) return false;
    stack_iterator_state_t *state = iter->state;
    return state->step < state->stack->deque.list.size;
}

static void *stack_next(iterator_t *iter) {
    if (!iter || !iter->state) return NULL;
    stack_iterator_state_t *state = iter->state;

    if (!state->current || state->step >= state->stack->deque.list.size) return NULL;

    void *data = state->current->data;
    state->current = state->current->prev;
    state->step++;
    return data;
}

static void stack_iterator_destroy(iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create
iterator_t *stack_iterator_create(const stack_t *stack) {
    if (!stack || !stack->is_initialized) return NULL;

    stack_iterator_state_t *state = calloc(1, sizeof(stack_iterator_state_t));
    if (!state) return NULL;

    iterator_t *iter = calloc(1, sizeof(iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->stack = stack;
    state->current = stack->deque.list.tail;

    iter->container = (void *)stack;
    iter->state = state;
    iter->has_next = stack_has_next;
    iter->next = stack_next;
    iter->destroy = stack_iterator_destroy;

    return iter;
}