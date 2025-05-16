/*
 * ccol/src/iterator/ccol_deque_iterator.c
 *
 * Iterator implementation for double-ended queue (deque).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdbool.h>

#include "ccol/ccol_deque.h"
#include "ccol/ccol_deque_iterator.h"
#include "ccol/ccol_iterator.h"

// Private
static bool ccol_deque_has_next(ccol_iterator_t *iter) {
    if (!iter || !iter->state) return false;
    ccol_deque_iterator_state_t *state = iter->state;
    return state->step < state->deque->list.size;
}

static void *ccol_deque_next(ccol_iterator_t *iter) {
    if (!iter || !iter->state) return NULL;
    ccol_deque_iterator_state_t *state = iter->state;

    if (!state->current || state->step >= state->deque->list.size) return NULL;

    void *data = state->current->data;
    state->current = state->current->next;
    state->step++;
    return data;
}

static void ccol_deque_iterator_destroy(ccol_iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create
ccol_iterator_t *ccol_deque_iterator_create(const ccol_deque_t *deque) {
    if (!deque || !deque->is_initialized) return NULL;

    ccol_deque_iterator_state_t *state = calloc(1, sizeof(ccol_deque_iterator_state_t));
    if (!state) return NULL;

    ccol_iterator_t *iter = calloc(1, sizeof(ccol_iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->deque = deque;
    state->current = deque->list.head;

    iter->container = (void *)deque;
    iter->state = state;
    iter->has_next = ccol_deque_has_next;
    iter->next = ccol_deque_next;
    iter->destroy = ccol_deque_iterator_destroy;

    return iter;
}
