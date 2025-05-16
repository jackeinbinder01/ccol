/*
 * ccol/src/iterator/ccol_vector_iterator.c
 *
 * Iterator implementation for dynamic array (vector).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "ccol/ccol_vector.h"
#include "ccol/ccol_iterator.h"

ccol_iterator_t *ccol_vector_iterator_create(const ccol_vector_t *vec);