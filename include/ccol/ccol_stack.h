/*
 * ccol/ccol_stack.h
 *
 * Stack (LIFO) API.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_STACK_H
#define CCOL_STACK_H

#include <stddef.h>
#include <stdbool.h>

#include "ccol_constants.h"
#include "ccol_status.h"
#include "ccol_deque.h"

typedef struct ccol_stack {
    ccol_deque_t *deque;
    bool is_initialized;
} ccol_stack_t;

// Create / Initialize
ccol_status_t ccol_stack_init(
    ccol_stack_t *stack,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

ccol_status_t ccol_stack_create(
    ccol_stack_t **stack_out,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
);

// Insertion
ccol_status_t ccol_stack_push(ccol_stack_t *stack, void *data);

// Removal
ccol_status_t ccol_stack_pop(ccol_stack_t *stack, void **data_out);

// Access
ccol_status_t ccol_stack_peek(const ccol_stack_t *stack, void **data_out);

// Attributes
bool ccol_stack_is_empty(const ccol_stack_t *stack);
size_t ccol_stack_size(const ccol_stack_t *stack);

// Copy / Clone
ccol_status_t ccol_stack_clone(const ccol_stack_t *src, ccol_stack_t **stack_out);
ccol_status_t ccol_stack_deep_clone(const ccol_stack_t *src, ccol_stack_t **stack_out);
ccol_status_t ccol_stack_shallow_clone(const ccol_stack_t *src, ccol_stack_t **stack_out);

ccol_status_t ccol_stack_copy(ccol_stack_t *dest, const ccol_stack_t *src);
ccol_status_t ccol_stack_deep_copy(ccol_stack_t *dest, const ccol_stack_t *src);
ccol_status_t ccol_stack_shallow_copy(ccol_stack_t *dest, const ccol_stack_t *src);

// Cleanup
ccol_status_t ccol_stack_clear(ccol_stack_t *stack);
ccol_status_t ccol_stack_destroy(ccol_stack_t *stack);
ccol_status_t ccol_stack_free(ccol_stack_t **stack_ptr);

// Print / Debug
ccol_status_t ccol_stack_print(const ccol_stack_t *stack);

#endif  // CCOL_STACK_H
