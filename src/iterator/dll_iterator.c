/*
 * ccol/dll_iterator.c
 *
 * Iterator functions for dll
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdbool.h>

#include "dll.h"
#include "dll_iterator.h"
#include "iterator.h"

// Private
static bool dll_has_next(iterator_t *iter) {
    if (!iter || !iter->state) return false;
    dll_iterator_state_t *state = iter->state;
    return state->current != NULL;
}

static void *dll_next(iterator_t *iter) {
    if (!iter || !iter->state) return NULL;
    dll_iterator_state_t *state = iter->state;
    if (!state->current) return NULL;

    void *data = state->current->data;
    state->current = state->current->next;
    return data;
}

static void dll_iterator_destroy(iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create
iterator_t *dll_iterator_create(const dll_t *dll) {
    if (!dll || !dll->is_initialized) return NULL;

    dll_iterator_state_t *state = calloc(1, sizeof(dll_iterator_state_t));
    if (!state) return NULL;

    iterator_t *iter = calloc(1, sizeof(iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->dll = dll;
    state->current = dll->head;

    iter->container = (void *)dll;
    iter->state = state;
    iter->has_next = dll_has_next;
    iter->next = dll_next;
    iter->destroy = dll_iterator_destroy;

    return iter;
}
