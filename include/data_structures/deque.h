/*
* deque.h / Practicum 1
*
* Jack Einbinder / CS5600 / Northeastern University
* Spring 2025 / March 19, 2025
*
*/

#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>
#include "cdll.h"


typedef struct deque_t {
    cdll_t* list;
} deque_t;

/* Operation Prototypes */
deque_t* deque_init(void);
void deque_destroy(deque_t* deque, void (*free_data)(void*));
int deque_push(deque_t* deque, void* data);
int deque_push_left(deque_t* deque, void* data);
void* deque_pop(deque_t* deque);
void* deque_pop_left(deque_t* deque);
int deque_delete(deque_t* deque, dll_node_t* node);
dll_node_t* deque_search(const deque_t* deque, const void* data, int (*cmp)(const void*, const void*));
int deque_is_empty(deque_t* deque);
size_t deque_size(deque_t* deque);
void deque_print(deque_t* deque);

#endif //DEQUE_H
