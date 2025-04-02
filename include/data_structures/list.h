/*
 * ccol/list.h
 *
 * Linked list
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include "iterator.h"

typedef struct list_node_t {
  void *data;
  struct list_node_t *next;
} list_node_t;

typedef struct list_t {
    list_node_t *head;
    list_node_t *tail;
    size_t size;
} list_t;

// Constructors
void list_init(list_t *list);
list_t *list_create(void);

// Insertion
void list_push_back(list_t *list, void *data);
void list_push_middle(list_t *list, void *data);
void list_push_front(list_t *list, void *data);

// Removal
void *list_remove(list_t *list, void *data);
void *list_pop(list_t *list);
void *list_pop_middle(list_t *list);
void *list_pop_front(list_t *list);

// Access
void *list_get(const list_t *list, size_t index);
void *list_search(const list_t *list, const void *data, int (*cmp)(const void *, const void *));
void *list_peek_back(const list_t *list);
void *list_peek_middle(const list_t *list);
void *list_peek_front(const list_t *list);

// Attributes
size_t list_size(const list_t *list);
int list_is_empty(const list_t *list);
int list_contains(const list_t *list, void *data);

// Print
void list_print(const list_t *list);

// Cleanup
void list_free(list_t *list);
void list_destroy(list_t *list, void (*free_data)(void *));
void list_clear(list_t *list);

// Utilities
void list_set(list_t *list, size_t index, void *data);
list_t *list_clone(const list_t *list);
void list_swap(list_t *list, size_t i, size_t j);
size_t list_index_of(const list_t *list, void *data);
void list_reverse(list_t *list);

// Iterator
iterator_t *list_iterator_create(const list_t *list);

#define LIST_FOR(type, var, list_ptr)                                             \
    for (iterator_t *_it = list_iterator_create(list_ptr); _it; _it = NULL)       \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // LIST_H
