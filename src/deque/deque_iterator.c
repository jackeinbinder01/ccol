/*
* ccol/deque_iterator.c
 *
 * Iterator functions for deque
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdbool.h>

#include "deque.h"
#include "deque_iterator.h"
#include "iterator.h"

// Private
static bool deque_has_next(iterator_t *iter) {
    if (!iter || !iter->state) return false;
    deque_iterator_state_t *state = iter->state;
    return state->step < state->deque->list.size;
}

static void *deque_next(iterator_t *iter) {
    if (!iter || !iter->state) return NULL;
    deque_iterator_state_t *state = iter->state;

    if (!state->current || state->step >= state->deque->list.size) return NULL;

    void *data = state->current->data;
    state->current = state->current->next;
    state->step++;
    return data;
}

static void deque_iterator_destroy(iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create
iterator_t *deque_iterator_create(const deque_t *deque) {
    if (!deque || !deque->is_initialized) return NULL;

    deque_iterator_state_t *state = calloc(1, sizeof(deque_iterator_state_t));
    if (!state) return NULL;

    iterator_t *iter = calloc(1, sizeof(iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->deque = deque;
    state->current = deque->list.head;

    iter->container = (void *)deque;
    iter->state = state;
    iter->has_next = deque_has_next;
    iter->next = deque_next;
    iter->destroy = deque_iterator_destroy;

    return iter;
}
