/*
 * ccol/queue_iterator.h
 *
 * Iterator functions for queue
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"
#include "queue_iterator.h"
#include "iterator.h"

// Private
static bool queue_has_next(iterator_t *iter) {
    if (!iter || !iter->state) return false;
    queue_iterator_state_t *state = iter->state;
    return state->step < state->queue->deque.list.size;
}

static void *queue_next(iterator_t *iter) {
    if (!iter || !iter->state) return NULL;
    queue_iterator_state_t *state = iter->state;

    if (!state->current || state->step >= state->queue->deque.list.size) return NULL;

    void *data = state->current->data;
    state->current = state->current->next;
    state->step++;
    return data;
}

static void queue_iterator_destroy(iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create
iterator_t *queue_iterator_create(const queue_t *queue) {
    if (!queue || !queue->is_initialized) return NULL;

    queue_iterator_state_t *state = calloc(1, sizeof(queue_iterator_state_t));
    if (!state) return NULL;

    iterator_t *iter = calloc(1, sizeof(iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->queue = queue;
    state->current = queue->deque.list.head;

    iter->container = (void *)queue;
    iter->state = state;
    iter->has_next = queue_has_next;
    iter->next = queue_next;
    iter->destroy = queue_iterator_destroy;

    return iter;
}