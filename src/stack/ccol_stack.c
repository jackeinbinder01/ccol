/*
 * ccol/src/stack/ccol_stack.c
 *
 * Stack (LIFO) implementation.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ccol/ccol_stack.h"
#include "ccol/ccol_deque.h"
#include "ccol/ccol_macros.h"
#include "ccol/ccol_status.h"

#include "../cdll/internal.h"

// Create / Initialize
ccol_status_t ccol_stack_init(
    ccol_stack_t *stack,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
) {
    if (!stack) return CCOL_STATUS_INVALID_ARG;

    stack->deque = malloc(sizeof(deque_t));
    if (!stack->deque) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_deque_init(stack->deque, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(stack->deque);
        return status;
    }

    stack->is_initialized = true;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_stack_create(
    ccol_stack_t **stack_out,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
) {
    if (!stack_out) return CCOL_STATUS_INVALID_ARG;

    *stack_out = NULL;

    ccol_stack_t *stack = calloc(1, sizeof(ccol_stack_t));
    if (!stack) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_stack_init(stack, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(stack);
        return status;
    }

    *stack_out = stack;
    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t ccol_stack_push(ccol_stack_t *stack, void *data) {
    CCOL_CHECK_INIT(stack);
    return ccol_deque_push_back(stack->deque, data);
}

// Removal
ccol_status_t ccol_stack_pop(ccol_stack_t *stack, void **data_out) {
    CCOL_CHECK_INIT(stack);
    return ccol_deque_pop_back(stack->deque, data_out);
}

// Access
ccol_status_t ccol_stack_peek(const ccol_stack_t *stack, void **data_out) {
    CCOL_CHECK_INIT(stack);
    return ccol_deque_peek_back(stack->deque, data_out);
}

// Attributes
bool ccol_stack_is_empty(const ccol_stack_t *stack) {
    if (!stack || !stack->is_initialized) return true;
    return ccol_deque_is_empty(stack->deque);
}

size_t ccol_stack_size(const ccol_stack_t *stack) {
    if (!stack || !stack->is_initialized) return 0;
    return ccol_deque_size(stack->deque);
}

// Copy / Clone
ccol_status_t ccol_stack_deep_clone(const ccol_stack_t *src, ccol_stack_t **stack_out) {
    CCOL_CHECK_INIT(src);
    if (!stack_out) return CCOL_STATUS_INVALID_ARG;

    *stack_out = NULL;

    ccol_stack_t *clone = calloc(1, sizeof(ccol_stack_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_stack_init(
        clone,
        src->deque->list->copier,
        src->deque->list->freer,
        src->deque->list->printer,
        src->deque->list->comparator
    );
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    status = ccol__cdll_clone_into(src->deque->list, clone->deque->list);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    *stack_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_stack_shallow_clone(const ccol_stack_t *src, ccol_stack_t **stack_out) {
    CCOL_CHECK_INIT(src);
    if (!stack_out) return CCOL_STATUS_INVALID_ARG;

    *stack_out = NULL;

    ccol_stack_t *clone = calloc(1, sizeof(ccol_stack_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    deque_t *deque_clone = NULL;
    ccol_status_t status = ccol_deque_shallow_clone(src->deque, &deque_clone);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    clone->deque = deque_clone;

    *stack_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_stack_clone(const ccol_stack_t *src, ccol_stack_t **stack_out) {
    return ccol_stack_deep_clone(src, stack_out);
}

ccol_status_t ccol_stack_deep_copy(ccol_stack_t *dest, const ccol_stack_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = ccol_deque_clear(dest->deque);
    if (status != CCOL_STATUS_OK) {
        dest->deque->list->head = NULL;
        dest->deque->list->tail = NULL;
        dest->deque->list->size = 0;
        return status;
    }

    return ccol_deque_deep_copy(dest->deque, src->deque);
}
ccol_status_t ccol_stack_shallow_copy(ccol_stack_t *dest, const ccol_stack_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = ccol_deque_clear(dest->deque);
    if (status != CCOL_STATUS_OK) {
        dest->deque->list->head = NULL;
        dest->deque->list->tail = NULL;
        dest->deque->list->size = 0;
        return status;
    }

    return ccol_deque_shallow_copy(dest->deque, src->deque);
}

ccol_status_t ccol_stack_copy(ccol_stack_t *dest, const ccol_stack_t *src) {
    return ccol_stack_deep_copy(dest, src);
}

// Cleanup
ccol_status_t ccol_stack_clear(ccol_stack_t *stack) {
    CCOL_CHECK_INIT(stack);
    return ccol_deque_clear(stack->deque);
}

ccol_status_t ccol_stack_destroy(ccol_stack_t *stack) {
    CCOL_CHECK_INIT(stack);
    ccol_status_t status = ccol_deque_clear(stack->deque);
    if (status != CCOL_STATUS_OK) return status;

    return ccol__stack_uninit(stack);
}

ccol_status_t ccol_stack_free(ccol_stack_t **stack_ptr) {
    if (!stack_ptr || !*stack_ptr || !(*stack_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = ccol_stack_destroy(*stack_ptr);

    free(*stack_ptr);
    *stack_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t ccol_stack_print(const ccol_stack_t *stack) {
    CCOL_CHECK_INIT(stack);
    return ccol_deque_print(stack->deque);
}