/*
 * ccol/dll.h
 *
 * Doubly-linked list
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dll.h"
#include "ccol_status.h"
#include "ccol_macros.h"

// Private
static dll_node_t *dll_get_middle_node(const dll_t *dll) {
    if (!dll || !dll->is_initialized || dll->size == 0) return NULL;

    size_t middle_index = dll->size / 2;
    dll_node_t * middle_node = NULL;

    if (middle_index < dll->size - middle_index) {
        middle_node = dll->head;
        for (size_t i = 0; i < middle_index; i++) {
            middle_node = middle_node->next;
        }
    } else {
        middle_node = dll->tail;
        for (size_t i = dll->size - 1; i > middle_index; i--) {
            middle_node = middle_node->prev;
        }
    }

    return middle_node;
}

// Constructors
ccol_status_t dll_create(dll_t **dll_out) {
    if (!dll_out) return CCOL_STATUS_INVALID_ARG;

    dll_t* dll = malloc(sizeof(dll_t));
    if (!dll) return CCOL_STATUS_ALLOC;

    dll_init(dll);
    *dll_out = dll;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_init(dll_t *dll) {
    if (!dll) return CCOL_STATUS_INVALID_ARG;

    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    dll->is_initialized = true;

    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t dll_push_back(dll_t *dll, void *data) {
    CCOL_CHECK_INIT(dll);

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = dll->tail;

    if (dll->tail) {
        dll->tail->next = new_node;
    } else {
        dll->head = new_node;
    }

    dll->tail = new_node;
    dll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_push_middle(dll_t *dll, void *data) {
    CCOL_CHECK_INIT(dll);

    if (dll->size == 0) {
        return dll_push_back(dll, data);
    }

    dll_node_t *middle = dll_get_middle_node(dll);
    return dll_insert_after(dll, middle, data);
}

ccol_status_t dll_push_front(dll_t *dll, void *data) {
    CCOL_CHECK_INIT(dll);

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    new_node->data = data;
    new_node->next = dll->head;
    new_node->prev = NULL;

    if (dll->head) {
        dll->head->prev = new_node;
    } else {
        dll->tail = new_node;
    }

    dll->head = new_node;
    dll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_insert_after(dll_t *dll, dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(dll);
    if (!ref_node) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    new_node->data = data;

    new_node->next = ref_node->next;
    new_node->prev = ref_node;
    ref_node->next = new_node;

    if (new_node->next) {
        new_node->next->prev = new_node;
    } else {
        dll->tail = new_node;
    }

    dll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_insert_before(dll_t *dll, dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(dll);
    if (!ref_node) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    new_node->data = data;

    new_node->next = ref_node;
    new_node->prev = ref_node->prev;

    if (ref_node->prev) {
        ref_node->prev->next = new_node;
    } else {
        dll->head = new_node;
    }
    ref_node->prev = new_node;

    dll->size++;
    return CCOL_STATUS_OK;
}

// Removal
ccol_status_t dll_remove(dll_t *dll, void *data, int (*cmp)(const void *, const void *)) {
    CCOL_CHECK_INIT(dll);

    dll_node_t *node = dll_search(dll, data, cmp);
    if (!node) return CCOL_STATUS_NOT_FOUND;

    dll_remove_node(dll, node);
    return CCOL_STATUS_OK;
}

ccol_status_t dll_remove_node(dll_t *dll, dll_node_t* node) {
    CCOL_CHECK_INIT(dll);
    if (!node) return CCOL_STATUS_INVALID_ARG;

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        dll->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        dll->tail = node->prev;
    }

    free(node);
    dll->size--;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_pop(dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!dll->tail) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *tail = dll->tail;
    *data_out = tail->data;

    return dll_remove_node(dll, tail);
}

void *dll_pop_middle(dll_t *dll) {
    if (!dll || !dll->is_initialized || dll->size == 0) return NULL;

    if (dll->size == 1) {
        return dll_pop(dll);
    }

    dll_node_t *middle = dll_get_middle_node(dll);
    void *data = middle->data;
    dll_remove_node(dll, middle);

    return data;
}

void *dll_pop_front(dll_t *dll) {
    if (!dll || !dll->is_initialized || !dll->head) return NULL;

    dll_node_t *head = dll->head;
    void *data = head->data;
    dll_remove_node(dll, head);

    return data;
}

// Access
void *dll_get(const dll_t *dll, size_t index);

dll_node_t *dll_search(const dll_t *dll, const void *data, int (*cmp)(const void *, const void *));

void *dll_peek_back(const dll_t *dll) {
    if (!dll || !dll->is_initialized || !dll->tail) return NULL;

    return dll->tail->data;
}
void *dll_peek_middle(const dll_t *dll) {
    if (!dll || !dll->is_initialized || dll->size == 0) return NULL;

    dll_node_t *middle = dll_get_middle_node(dll);

    return middle->data;
}
void *dll_peek_front(const dll_t *dll) {
    if (!dll || !dll->is_initialized || !dll->head) return NULL;

    return dll->head->data;
}

// Attributes
size_t dll_size(const dll_t *dll) {
    if (!dll || !dll->is_initialized) return 0;
    return dll->size;
}

bool dll_is_empty(const dll_t *dll) {
    return (!dll || !dll->is_initialized || dll->size == 0);
}

bool dll_contains(const dll_t *dll, const void *data, int (*cmp)(const void *, const void *)) {
    return dll && dll->is_initialized && dll->size > 0 && dll_search(dll, data, cmp);
}

// Print
void dll_print(const dll_t *dll);

// Cleanup
void dll_destroy(dll_t *dll, void (*free_data)(void*));
void dll_free(dll_t *dll);
void dll_clear(dll_t *dll, void (*free_data)(void *));

// Utilities
ccol_status_t dll_set(dll_t *dll, size_t index, void *data);
ccol_status_t dll_clone(const dll_t *src, dll_t **dll_out);
ccol_status_t dll_copy(dll_t *dest, const dll_t *src);
ccol_status_t dll_swap(dll_t *dll, size_t i, size_t j);
size_t dll_index_of(const dll_t *dll, void *data);
ccol_status_t dll_reverse(dll_t *dll);

// Iterator
iterator_t *dll_iterator_create(const dll_t *dll);



