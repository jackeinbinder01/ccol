/*
 * ccol/stack.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>
#include "iterator.h"
#include "deque.h"

typedef struct stack_t {
    deque_t deque;
    bool is_initialized;
} stack_t;

// Constructors
void stack_init(stack_t *stack);
stack_t *stack_create(void);

// Insertion
void stack_push(stack_t *stack, void *data);

// Removal
void* stack_pop(stack_t *stack);

// Access
void* stack_peek(const stack_t *stack);

// Attributes
size_t stack_size(const stack_t *stack);
bool stack_is_empty(const stack_t *stack);
bool stack_contains(const stack_t *stack, void *data);

// Print
void stack_print(const stack_t *stack);

// Cleanup
void stack_free(stack_t *stack);
void stack_destroy(stack_t *stack, void (*free_data)(void *));
void stack_clear(stack_t *stack, void (*free_data)(void *));

// Utilities
void stack_set(stack_t *stack, size_t index, void *data);
stack_t *stack_clone(const stack_t *stack);
void stack_copy(stack_t *dest, const stack_t *src);
void stack_swap(stack_t *stack, size_t i, size_t j);
size_t stack_index_of(const stack_t *stack, void *data);
void stack_reverse(stack_t *stack);

// Iterator
iterator_t *stack_iterator_create(const stack_t *stack);

#define STACK_FOR(type, var, stack_ptr)                                           \
    for (iterator_t *_it = stack_iterator_create(stack_ptr); _it; _it = NULL)     \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // STACK_H
