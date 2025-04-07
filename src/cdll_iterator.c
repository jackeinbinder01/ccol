/*
 * ccol/cdll_iterator.c
 *
 * Iterator functions for cdll
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include "cdll.h"
#include "cdll_iterator.h"
#include "iterator.h"

// Private
static bool cdll_has_next(iterator_t *iter) {
    if (!iter || !iter->state) return false;
    cdll_iterator_state_t *state = iter->state;
    return state->step < state->cdll->size;
}

static void *cdll_next(iterator_t *iter) {
    if (!iter || !iter->state) return false;
    cdll_iterator_state_t *state = iter->state;

    if (!state->current || state->step >= state->cdll->size) return NULL;

    void *data = state->current->data;
    state->current = state->current->next;
    state->step++;
    return data;
}

static void cdll_iterator_destroy(iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create
iterator_t *cdll_iterator_create(const cdll_t *cdll) {
    if (!cdll || !cdll->is_initialized) return NULL;

    cdll_iterator_state_t *state = calloc(1, sizeof(cdll_iterator_state_t));
    if (!state) return NULL;

    iterator_t *iter = calloc(1, sizeof(iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->cdll = cdll;
    state->current = cdll->head;

    iter->container = (void *)cdll;
    iter->state = state;
    iter->has_next = cdll_has_next;
    iter->next = cdll_next;
    iter->destroy = cdll_iterator_destroy;

    return iter;
}