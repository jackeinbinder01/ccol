/*
 * ccol/stack.h
 *
 * LIFO stack
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "stack.h"
#include "ccol_macros.h"
#include "ccol_status.h"

// Create / Initialize
ccol_status_t stack_init(
    stack_t *stack,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
);

ccol_status_t stack_create(
    stack_t **stack_out,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
);

// Insertion
ccol_status_t stack_push(stack_t *stack, void *data);

// Removal
ccol_status_t stack_pop(stack_t *stack, void **data_out);

// Access
ccol_status_t stack_peek(const stack_t *stack, void **data_out);

// Attributes
bool stack_is_empty(const stack_t *stack);
size_t stack_size(const stack_t *stack);

// Copy / Clone
ccol_status_t stack_clone(const stack_t *src, stack_t **stack_out);
ccol_status_t stack_deep_clone(const stack_t *src, stack_t **stack_out);
ccol_status_t stack_shallow_clone(const stack_t *src, stack_t **stack_out);

ccol_status_t stack_copy(stack_t *dest, const stack_t *src);
ccol_status_t stack_deep_copy(stack_t *dest, const stack_t *src);
ccol_status_t stack_shallow_copy(stack_t *dest, const stack_t *src);

// Cleanup
ccol_status_t stack_clear(stack_t *stack);
ccol_status_t stack_destroy(stack_t *stack);
ccol_status_t stack_free(stack_t **stack_ptr);

// Print / Debug
ccol_status_t stack_print(const stack_t *stack);