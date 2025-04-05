/*
 * ccol/dll.h
 *
 * Doubly linked list
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef DLL_H
#define DLL_H

#include <stddef.h>
#include <stdbool.h>
#include "iterator.h"

typedef struct dll_node_t {
    void *data;
    struct dll_node_t *next;
    struct dll_node_t *prev;
} dll_node_t;

typedef struct dll_t {
    dll_node_t *head;
    dll_node_t *tail;
    size_t size;

    bool is_initialized;
} dll_t;

// Constructors
void dll_init(dll_t *dll);
dll_t *dll_create(void);

// Insertion
void dll_push_back(dll_t *dll, void *data);
void dll_push_middle(dll_t *dll, void *data);
void dll_push_front(dll_t *dll, void *data);
void dll_insert_after(dll_t *dll, dll_node_t* ref_node, void *data);
void dll_insert_before(dll_t *dll, dll_node_t* ref_node, void *data);

// Removal
void *dll_remove(dll_t *dll, void *data);
void dll_remove_node(dll_t *dll, dll_node_t* node);
void *dll_pop(dll_t *dll);
void *dll_pop_middle(dll_t *dll);
void *dll_pop_front(dll_t *dll);

// Access
void *dll_get(const dll_t *dll, size_t index);
void *dll_search(const dll_t *dll, const void *data, int (*cmp)(const void *, const void *));
void *dll_peek_back(const dll_t *dll);
void *dll_peek_middle(const dll_t *dll);
void *dll_peek_front(const dll_t *dll);

// Attributes
size_t dll_size(const dll_t *dll);
bool dll_is_empty(const dll_t *dll);
bool dll_contains(const dll_t *dll, void *data);

// Print
void dll_print(dll_t *dll);

// Cleanup
void dll_destroy(dll_t *dll, void (*free_data)(void*));
void dll_free(dll_t *dll);
void dll_clear(dll_t *dll, void (*free_data)(void *));

// Utilities
void dll_set(dll_t *dll, size_t index, void *data);
dll_t *dll_clone(const dll_t *dll);
void dll_copy(dll_t *dest, const dll_t *src);
void dll_swap(dll_t *dll, size_t i, size_t j);
size_t dll_index_of(const dll_t *dll, void *data);
void dll_reverse(dll_t *dll);

// Iterator
iterator_t *dll_iterator_create(const dll_t *dll);

#define DLL_FOR(type, var, dll_ptr)                                               \
    for (iterator_t *_it = dll_iterator_create(dll_ptr); _it; _it = NULL)         \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // DLL_H
