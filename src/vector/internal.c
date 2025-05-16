/*
 * ccol/src/vector/internal.c
 *
 * Internal helper function implementations for dynamic array (vector).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdbool.h>
#include <stdlib.h>

#include "ccol/ccol_vector.h"
#include "ccol/ccol_macros.h"

#include "vector/internal.h"

ccol_status_t ccol__vector_uninit(ccol_vector_t *vec) {
    CCOL_CHECK_INIT(vec);

    free(vec->data);
    vec->data = NULL;
    vec->size = vec->capacity = vec->element_size = 0;

    vec->copier = (ccol_copy_t){0};
    vec->freer = (ccol_free_t){0};
    vec->printer = (ccol_print_t){0};
    vec->comparator = (ccol_comparator_t){0};

    vec->is_initialized = false;

    return CCOL_STATUS_OK;
}

