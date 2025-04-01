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
  struct list_node_t* next;
} list_node_t;

typedef struct list_t {
    list_node_t* head;
    list_node_t* tail;
    size_t size;
} list_t;

// Constructors
void list_init(void);
list_t* list_create(void);

// Insertion
void list_push_back(list_t* list, void* data);
void list_push_middle(list_t* list, void* data);
void list_push_front(list_t* list, void* data);

// Removal
void* list_remove(list_t* list, void* data);
void* list_pop(list_t* list);
void* list_pop_front(list_t* list);

// Access
void* list_get(const list_t* vector, size_t index);
void* list_peek_back(const list_t* vector);
void* list_peek_middle(const list_t* vector);
void* list_peek_front(const list_t* vector);

// Attributes
size_t list_size(const list_t* list);
int list_is_empty(const list_t* list);
int list_contains(const list_t* list, void* data);

// Print
void list_print(const list_t* list);

// Cleanup
void list_free(list_t* list);
void list_destroy(list_t* list);
void list_clear(list_t* list);

// Iterator
iterator_t* list_iterator_create(const list_t* list);

#endif
