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
#include "ccol_macros.h"

ccol_status_t vector_uninit(vector_t *vec) {
    CCOL_CHECK_INIT(vec);

    free(vec->data);
    vec->data = NULL;
    vec->size = vec->capacity = vec->element_size = 0;

    vec->copier = (copy_t){0};
    vec->freer = (free_t){0};
    vec->printer = (print_t){0};
    vec->comparator = (comparator_t){0};

    vec->is_initialized = false;

    return CCOL_STATUS_OK;
}

