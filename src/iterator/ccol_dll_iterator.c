/*
 * ccol/src/iterator/ccol_dll_iterator.c
 *
 * Iterator implementation for doubly-linked list (dll).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdbool.h>

#include "ccol/ccol_dll.h"
#include "ccol/ccol_dll_iterator.h"
#include "ccol/ccol_iterator.h"

// Private
static bool ccol_dll_has_next(ccol_iterator_t *iter) {
    if (!iter || !iter->state) return false;
    ccol_dll_iterator_state_t *state = iter->state;
    return state->current != NULL;
}

static void *ccol_dll_next(ccol_iterator_t *iter) {
    if (!iter || !iter->state) return NULL;
    ccol_dll_iterator_state_t *state = iter->state;
    if (!state->current) return NULL;

    void *data = state->current->data;
    state->current = state->current->next;
    return data;
}

static void ccol_dll_iterator_destroy(ccol_iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create
ccol_iterator_t *ccol_dll_iterator_create(const ccol_dll_t *dll) {
    if (!dll || !dll->is_initialized) return NULL;

    ccol_dll_iterator_state_t *state = calloc(1, sizeof(ccol_dll_iterator_state_t));
    if (!state) return NULL;

    ccol_iterator_t *iter = calloc(1, sizeof(ccol_iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->dll = dll;
    state->current = dll->head;

    iter->container = (void *)dll;
    iter->state = state;
    iter->has_next = ccol_dll_has_next;
    iter->next = ccol_dll_next;
    iter->destroy = ccol_dll_iterator_destroy;

    return iter;
}
