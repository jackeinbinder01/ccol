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
#include <stdlib.h>
#include <stdio.h>
#include "components/message.h"

/*
 * This is the API for a doubly linked list.
 */

typedef struct dll_node_t {
    void* data;
    struct dll_node_t* next;
    struct dll_node_t* prev;
} dll_node_t;

typedef struct dll_t {
    dll_node_t* head;
    dll_node_t* tail;
    size_t size;
} dll_t;

dll_t* dll_init(void);
void dll_destroy(dll_t* dll, void (*free_data)(void*));
int dll_prepend(dll_t* dll, void* data);
int dll_append(dll_t* dll, void* data);
int dll_insert_after(dll_t* dll, dll_node_t* target_node, void* data);
int dll_insert_before(dll_t* dll, dll_node_t* target_node, void* data);
int dll_delete(dll_t* dll, dll_node_t* node);
dll_node_t* dll_pop(dll_t* dll);
dll_node_t* dll_pop_left(dll_t* dll);
dll_node_t* dll_search(const dll_t* dll, const void* data, int (*cmp)(const void*, const void*));
size_t dll_size(const dll_t* dll);
int dll_is_empty(const dll_t* dll);
void dll_print_idx(dll_t* dll);
void dll_print_node(dll_node_t* node);
void dll_print(dll_t* dll);

#endif //DLL_H
