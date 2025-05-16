/*
 * ccol/src/iterator/ccol_cdll_iterator.c
 *
 * Iterator implementation for circular doubly-linked list (cdll).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdbool.h>

#include "ccol/ccol_cdll.h"
#include "ccol/ccol_cdll_iterator.h"
#include "ccol/ccol_iterator.h"

// Private
static bool ccol_cdll_has_next(ccol_iterator_t *iter) {
    if (!iter || !iter->state) return false;
    ccol_cdll_iterator_state_t *state = iter->state;
    return state->step < state->cdll->size;
}

static void *ccol_cdll_next(ccol_iterator_t *iter) {
    if (!iter || !iter->state) return NULL;
    ccol_cdll_iterator_state_t *state = iter->state;

    if (!state->current || state->step >= state->cdll->size) return NULL;

    void *data = state->current->data;
    state->current = state->current->next;
    state->step++;
    return data;
}

static void ccol_cdll_iterator_destroy(ccol_iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create
ccol_iterator_t *ccol_cdll_iterator_create(const ccol_cdll_t *cdll) {
    if (!cdll || !cdll->is_initialized) return NULL;

    ccol_cdll_iterator_state_t *state = calloc(1, sizeof(ccol_cdll_iterator_state_t));
    if (!state) return NULL;

    ccol_iterator_t *iter = calloc(1, sizeof(ccol_iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->cdll = cdll;
    state->current = cdll->head;

    iter->container = (void *)cdll;
    iter->state = state;
    iter->has_next = ccol_cdll_has_next;
    iter->next = ccol_dll_next;
    iter->destroy = ccol_cdll_iterator_destroy;

    return iter;
}
