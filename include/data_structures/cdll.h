/*
* cdll.h / Practicum 1
*
* Jack Einbinder / CS5600 / Northeastern University
* Spring 2025 / March 19, 2025
*
*/

#ifndef CDLL_H
#define CDLL_H

#include "dll.h"

/*
 * This is the API for a circular doubly linked list.
 */

typedef struct cdll_t {
    dll_node_t* head;
    dll_node_t* tail;
    size_t size;
} cdll_t;

cdll_t* cdll_init(void);
void cdll_destroy(cdll_t* cdll, void (*free_data)(void*));
int cdll_prepend(cdll_t* cdll, void* data);
int cdll_append(cdll_t* cdll, void* data);
int cdll_insert_after(cdll_t* cdll, dll_node_t* target_node, void* data);
int cdll_insert_before(cdll_t* cdll, dll_node_t* target_node, void* data);
int cdll_delete(cdll_t* cdll, dll_node_t* node);
dll_node_t* cdll_pop(cdll_t* cdll);
dll_node_t* cdll_pop_left(cdll_t* cdll);
dll_node_t* cdll_search(const cdll_t* cdll, const void* data, int (*cmp)(const void*, const void*));
size_t cdll_size(const cdll_t* cdll);
int cdll_is_empty(const cdll_t* cdll);
void cdll_print(cdll_t* cdll);

#endif //CDLL_H
