/*
 * ccol/stack.h
 *
 * LIFO stack
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "stack.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "deque.h"
#include "cdll_internal.h"
#include "ccol_macros.h"
#include "ccol_status.h"

// Create / Initialize
ccol_status_t stack_init(
    stack_t *stack,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
) {
    if (!stack) return CCOL_STATUS_INVALID_ARG;

    stack->deque = malloc(sizeof(deque_t));
    if (!stack->deque) return CCOL_STATUS_ALLOC;

    ccol_status_t status = deque_init(stack->deque, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(stack->deque);
        return status;
    }

    stack->is_initialized = true;
    return CCOL_STATUS_OK;

}

ccol_status_t stack_create(
    stack_t **stack_out,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
) {
    if (!stack_out) return CCOL_STATUS_INVALID_ARG;

    *stack_out = NULL;

    stack_t *stack = calloc(1, sizeof(stack_t));
    if (!stack) return CCOL_STATUS_ALLOC;

    ccol_status_t status = stack_init(stack, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(stack);
        return status;
    }

    *stack_out = stack;
    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t stack_push(stack_t *stack, void *data) {
    CCOL_CHECK_INIT(stack);
    return deque_push_back(stack->deque, data);
}

// Removal
ccol_status_t stack_pop(stack_t *stack, void **data_out) {
    CCOL_CHECK_INIT(stack);
    return deque_pop_back(stack->deque, data_out);
}

// Access
ccol_status_t stack_peek(const stack_t *stack, void **data_out) {
    CCOL_CHECK_INIT(stack);
    return deque_peek_back(stack->deque, data_out);
}

// Attributes
bool stack_is_empty(const stack_t *stack) {
    if (!stack || !stack->is_initialized) return true;
    return deque_is_empty(stack->deque);
}

size_t stack_size(const stack_t *stack) {
    if (!stack || !stack->is_initialized) return 0;
    return deque_size(stack->deque);
}

// Copy / Clone
ccol_status_t stack_deep_clone(const stack_t *src, stack_t **stack_out) {
    CCOL_CHECK_INIT(src);
    if (!stack_out) return CCOL_STATUS_INVALID_ARG;

    *stack_out = NULL;

    stack_t *clone = calloc(1, sizeof(stack_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    ccol_status_t status = stack_init(
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


    status = cdll_clone_into(src->deque->list, clone->deque->list);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    *stack_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t stack_shallow_clone(const stack_t *src, stack_t **stack_out) {
    CCOL_CHECK_INIT(src);
    if (!stack_out) return CCOL_STATUS_INVALID_ARG;

    *stack_out = NULL;

    stack_t *clone = calloc(1, sizeof(stack_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    deque_t *deque_clone = NULL;
    ccol_status_t status = deque_shallow_clone(src->deque, &deque_clone);
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    clone->deque = deque_clone;

    *stack_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t stack_clone(const stack_t *src, stack_t **stack_out) {
    return stack_deep_clone(src, stack_out);
}

ccol_status_t stack_deep_copy(stack_t *dest, const stack_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = deque_clear(dest->deque);
    if (status != CCOL_STATUS_OK) {
        dest->deque->list->head = NULL;
        dest->deque->list->tail = NULL;
        dest->deque->list->size = 0;
        return status;
    }

    return deque_deep_copy(dest->deque, src->deque);
}
ccol_status_t stack_shallow_copy(stack_t *dest, const stack_t *src) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = deque_clear(dest->deque);
    if (status != CCOL_STATUS_OK) {
        dest->deque->list->head = NULL;
        dest->deque->list->tail = NULL;
        dest->deque->list->size = 0;
        return status;
    }

    return deque_shallow_copy(dest->deque, src->deque);
}

ccol_status_t stack_copy(stack_t *dest, const stack_t *src) {
    return stack_deep_copy(dest, src);
}

// Cleanup
ccol_status_t stack_clear(stack_t *stack) {
    CCOL_CHECK_INIT(stack);
    return deque_clear(stack->deque);
}

ccol_status_t stack_destroy(stack_t *stack) {
    CCOL_CHECK_INIT(stack);

    ccol_status_t status = deque_destroy(stack->deque);
    if (status != CCOL_STATUS_OK) return status;

    free(stack->deque);
    stack->deque = NULL;

    stack->is_initialized = false;
    return CCOL_STATUS_OK;
}
ccol_status_t stack_free(stack_t **stack_ptr) {
    if (!stack_ptr || !*stack_ptr || !(*stack_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = stack_destroy(*stack_ptr);

    free(*stack_ptr);
    *stack_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t stack_print(const stack_t *stack) {
    CCOL_CHECK_INIT(stack);
    return deque_print(stack->deque);
}