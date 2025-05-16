/*
 * ccol/src/iterator/ccol_queue_iterator.c
 *
 * Iterator implementation for queue (FIFO).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdbool.h>

#include "ccol/ccol_queue.h"
#include "ccol/ccol_queue_iterator.h"
#include "ccol/ccol_iterator.h"

// Private
static bool ccol_queue_has_next(ccol_iterator_t *iter) {
    if (!iter || !iter->state) return false;
    ccol_queue_iterator_state_t *state = iter->state;
    return state->step < state->queue->deque.list.size;
}

static void *ccol_queue_next(ccol_iterator_t *iter) {
    if (!iter || !iter->state) return NULL;
    ccol_queue_iterator_state_t *state = iter->state;

    if (!state->current || state->step >= state->queue->deque.list.size) return NULL;

    void *data = state->current->data;
    state->current = state->current->next;
    state->step++;
    return data;
}

static void ccol_queue_iterator_destroy(ccol_iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create
ccol_iterator_t *ccol_queue_iterator_create(const ccol_queue_t *queue) {
    if (!queue || !queue->is_initialized) return NULL;

    ccol_queue_iterator_state_t *state = calloc(1, sizeof(ccol_queue_iterator_state_t));
    if (!state) return NULL;

    ccol_iterator_t *iter = calloc(1, sizeof(ccol_iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->queue = queue;
    state->current = queue->deque.list.head;

    iter->container = (void *)queue;
    iter->state = state;
    iter->has_next = ccol_queue_has_next;
    iter->next = ccol_queue_next;
    iter->destroy = ccol_queue_iterator_destroy;

    return iter;
}