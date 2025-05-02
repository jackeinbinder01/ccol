/*
 * ccol/vector_internal.c
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdbool.h>
#include <stdlib.h>

#include "vector.h"
#include "vector_internal.h"

void vector_uninit(vector_t *vec) {
    if (!vec || !vec->is_initialized) return;

    free(vec->data);
    vec->data = NULL;
    vec->size = vec->capacity = vec->element_size = 0;

    vec->copy_func = NULL;
    vec->free_func = NULL;
    vec->print_func = NULL;
    vec->cmp = NULL;
    vec->ctx = NULL;

    vec->is_initialized = false;
}

