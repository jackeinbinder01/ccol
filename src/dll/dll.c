/*
 * ccol/dll.c
 *
 * Doubly-linked list
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "dll.h"
#include "dll_internal.h"
#include "ccol_status.h"
#include "ccol_macros.h"
#include "ccol_constants.h"

// Create / Initialize
ccol_status_t dll_init(dll_t *dll) {
    if (!dll) return CCOL_STATUS_INVALID_ARG;

    dll->head = dll->tail = NULL;
    dll->size = 0;
    dll->is_initialized = true;

    return CCOL_STATUS_OK;
}

ccol_status_t dll_create(dll_t **dll_out) {
    if (!dll_out) return CCOL_STATUS_INVALID_ARG;

    dll_t* dll = calloc(1, sizeof(dll_t));
    if (!dll) return CCOL_STATUS_ALLOC;

    ccol_status_t status = dll_init(dll);
    if (status != CCOL_STATUS_OK) {
        free(dll);
        return status;
    }

    *dll_out = dll;
    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t dll_push(dll_t *dll, void *data) {
    return dll_push_back(dll, data);
}

ccol_status_t dll_push_front(dll_t *dll, void *data) {
    CCOL_CHECK_INIT(dll);

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    new_node->data = data;
    new_node->next = dll->head;
    new_node->prev = NULL;

    if (dll->head) dll->head->prev = new_node;
    else dll->tail = new_node;

    dll->head = new_node;
    dll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_push_middle(dll_t *dll, void *data) {
    CCOL_CHECK_INIT(dll);

    if (dll->size == 0) {
        return dll_push_back(dll, data);
    }

    const dll_node_t *head = dll->head;
    dll_node_t *middle = dll_get_middle_node(head, dll->size);
    return dll_insert_after(dll, middle, data);
}

ccol_status_t dll_push_back(dll_t *dll, void *data) {
    CCOL_CHECK_INIT(dll);

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = dll->tail;

    if (dll->tail) dll->tail->next = new_node;
    else dll->head = new_node;

    dll->tail = new_node;
    dll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_insert_before(dll_t *dll, dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(dll);
    if (!ref_node) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    if (ref_node == dll->head) return dll_push_front(dll, data);

    new_node->data = data;
    new_node->next = ref_node;
    new_node->prev = ref_node->prev;

    ref_node->prev->next = new_node;
    ref_node->prev = new_node;

    dll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_insert_after(dll_t *dll, dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(dll);
    if (!ref_node) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    if (ref_node == dll->tail) return dll_push_back(dll, data);

    new_node->data = data;
    new_node->prev = ref_node;
    new_node->next = ref_node->next;

    ref_node->next->prev = new_node;
    ref_node->next = new_node;

    dll->size++;
    return CCOL_STATUS_OK;
}

// Removal
ccol_status_t dll_pop(dll_t *dll, void **data_out) {
    return dll_pop_back(dll, data_out);
}

ccol_status_t dll_pop_front(dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!dll->head) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *head = dll->head;
    *data_out = head->data;

    return dll_remove_node(dll, head, NULL, NULL);
}

ccol_status_t dll_pop_middle(dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    if (dll->size == 1) {
        return dll_pop(dll, data_out);
    }

    const dll_node_t *head = dll->head;
    dll_node_t *middle = dll_get_middle_node(head, dll->size);
    *data_out = middle->data;

    return dll_remove_node(dll, middle, NULL, NULL);
}

ccol_status_t dll_pop_back(dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!dll->tail) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *tail = dll->tail;
    *data_out = tail->data;

    return dll_remove_node(dll, tail, NULL, NULL);
}

ccol_status_t dll_remove_node(dll_t *dll, dll_node_t* node, free_func_t free_data, void *ctx) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (!node) return CCOL_STATUS_INVALID_ARG;

    if (node->prev) node->prev->next = node->next;
    else dll->head = node->next;

    if (!node->next) dll->tail = node->prev;
    else node->next->prev = node->prev;

    dll_dispose_node(node, free_data, ctx);
    dll->size--;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_remove(dll_t *dll, void *data, comparator_t cmp, free_func_t free_data, void *ctx) {
    CCOL_CHECK_INIT(dll);

    dll_node_t *node = dll_search(dll, data, cmp, ctx);
    if (!node) return CCOL_STATUS_NOT_FOUND;

    return dll_remove_node(dll, node, free_data, ctx);
}

// Access
ccol_status_t dll_get(const dll_t *dll, size_t index, void **data_out){
    CCOL_CHECK_INIT(dll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (index > dll->size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;

    dll_node_t *target;
    if (index < dll->size / 2) {
        target = dll->head;
        for (size_t i = 0; i < index; i++) {
            target = target->next;
        }
    } else {
        target = dll->tail;
        for (size_t i = dll->size - 1; i != index; i--) {
            target = target->prev;
        }
    }
    *data_out = target->data;

    return CCOL_STATUS_OK;
}

ccol_status_t dll_get_node(const dll_t *dll, size_t index, dll_node_t **node_out) {
    CCOL_CHECK_INIT(dll);
    if (!node_out) return CCOL_STATUS_INVALID_ARG;
    if (index > dll->size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;

    return dll_get_node_bounded(dll->head, dll->tail, dll->size, index, node_out);
}

ccol_status_t dll_peek(const dll_t *dll, void **data_out) {
    return dll_peek_front(dll, data_out);
}

ccol_status_t dll_peek_front(const dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (!dll->head) return CCOL_STATUS_EMPTY;

    *data_out = dll->head->data;

    return CCOL_STATUS_OK;
}

ccol_status_t dll_peek_middle(const dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (dll->size == 0) return CCOL_STATUS_EMPTY;

    const dll_node_t *head = dll->head;
    dll_node_t *middle = dll_get_middle_node(head, dll->size);
    *data_out = middle->data;

    return CCOL_STATUS_OK;
}

ccol_status_t dll_peek_back(const dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (!dll->tail) return CCOL_STATUS_EMPTY;

    *data_out = dll->tail->data;

    return CCOL_STATUS_OK;
}

dll_node_t *dll_search(const dll_t *dll, const void *data, comparator_t cmp, void *ctx) {
    if (!dll || !dll->is_initialized || dll->size == 0 || !data || !cmp) return NULL;
    dll_node_t *head = dll->head;
    return dll_search_bounded(head, dll->size, data, cmp, ctx);
}

// Attributes
bool dll_is_empty(const dll_t *dll) {
    return (!dll || !dll->is_initialized || dll->size == 0);
}

size_t dll_size(const dll_t *dll) {
    if (!dll || !dll->is_initialized) return 0;
    return dll->size;
}

bool dll_contains(const dll_t *dll, const void *data, comparator_t cmp, void *ctx) {
    return dll_search(dll, data, cmp, ctx) != NULL;
}

bool dll_contains_node(const dll_t *dll, const dll_node_t *node) {
    if (!dll || !node) return false;

    dll_node_t *curr = dll->head;
    for (size_t i = 0; i < dll->size; i++, curr = curr->next) {
        if (curr == node) return true;
    }
    return false;
}

// Indexing
ccol_status_t dll_safe_index_of(const dll_t *dll, void *data, comparator_t cmp, void *ctx, size_t *out_index) {
    CCOL_CHECK_INIT(dll);
    if (!cmp || !out_index) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *curr = dll->head;
    for (size_t i = 0; i < dll->size; i++) {
        if (cmp(curr->data, data, ctx) == 0) {
            *out_index = i;
            return CCOL_STATUS_OK;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_NOT_FOUND;
}

size_t dll_index_of(const dll_t *dll, void *data, comparator_t cmp, void *ctx) {
    size_t index;
    ccol_status_t status = dll_safe_index_of(dll, data, cmp, ctx, &index);
    if (status != CCOL_STATUS_OK) return DLL_INDEX_NOT_FOUND;
    return index;
}

// Utilities
ccol_status_t dll_set(dll_t *dll, size_t index, void *data) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (index > dll->size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;

    dll_node_t *target;
    if (index < dll->size / 2) {
        target = dll->head;
        for (size_t i = 0; i < index; i++) {
            target = target->next;
        }
    } else {
        target = dll->tail;
        for (size_t i = dll->size - 1; i != index; i--) {
            target = target->prev;
        }
    }
    target->data = data;

    return CCOL_STATUS_OK;
}

ccol_status_t dll_swap_data(dll_t *dll, size_t i, size_t j) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (i > dll->size - 1 || j > dll->size -1) return CCOL_STATUS_OUT_OF_BOUNDS;

    if (i == j) return CCOL_STATUS_OK;

    dll_node_t *node_i = NULL, *node_j = NULL;

    ccol_status_t status_get_i = dll_get_node(dll, i, &node_i);
    ccol_status_t status_get_j = dll_get_node(dll, j, &node_j);
    if (status_get_i != CCOL_STATUS_OK || status_get_j != CCOL_STATUS_OK) return CCOL_STATUS_OUT_OF_BOUNDS;

    void *tmp = node_i->data;
    node_i->data = node_j->data;
    node_j->data = tmp;

    return CCOL_STATUS_OK;
}

ccol_status_t dll_swap_nodes(dll_t *dll, dll_node_t *x, dll_node_t *y) {
    CCOL_CHECK_INIT(dll);
    if (!x || !y) return CCOL_STATUS_INVALID_ARG;
    if (!dll_contains_node(dll, x) || !dll_contains_node(dll, y)) return CCOL_STATUS_INVALID_ARG;
    if (x == y || dll->size < 2) return CCOL_STATUS_OK;

    // Handle adjacent nodes
    if (x->next == y || y->next == x) {
        if (y->next == x) { // makes sure x comes first
            dll_node_t *tmp = x;
            x = y;
            y = tmp;
        }
        dll_node_t *x_prev = x->prev;
        dll_node_t *y_next = y->next;

        if (x_prev) x_prev->next = y;
        if (y_next) y_next->prev = x;

        y->prev = x_prev;
        x->next = y_next;
        y->next = x;
        x->prev = y;
    } else { // Handle non-adjacent nodes
        dll_node_t *x_prev = x->prev, *x_next = x->next;
        dll_node_t *y_prev = y->prev, *y_next = y->next;

        if (x_prev) x_prev->next = y;
        if (x_next) x_next->prev = y;
        if (y_prev) y_prev->next = x;
        if (y_next) y_next->prev = x;

        x->prev = y_prev;
        x->next = y_next;
        y->prev = x_prev;
        y->next = x_next;
    }

    // Swap list pointers
    if (dll->head == x) dll->head = y;
    else if (dll->head == y) dll->head = x;

    if (dll->tail == x) dll->tail = y;
    else if (dll->tail == y) dll->tail = x;

    return CCOL_STATUS_OK;
}

ccol_status_t dll_reverse(dll_t *dll) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (dll->size == 1) return CCOL_STATUS_OK;

    dll_node_t *curr = dll->head;
    for (size_t i = 0; i < dll->size; i++) {
      SWAP_PTR(curr->next, curr->prev);
      curr = curr->prev;
    }

    return SWAP_PTR(dll->head, dll->tail);
}

// Copy / Clone
ccol_status_t dll_clone(const dll_t *src, dll_t **dll_out, copy_func_t copy_data, void *ctx) {
    CCOL_CHECK_INIT(src);
    if (!dll_out || !copy_data) return CCOL_STATUS_INVALID_ARG;

    *dll_out = NULL;

    ccol_status_t status = dll_create(dll_out);
    if (status != CCOL_STATUS_OK) return status;

    dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        void *data_copy = copy_data(curr->data, ctx);
        status = dll_push_back(*dll_out, data_copy);
        if (status != CCOL_STATUS_OK) {
            dll_destroy(*dll_out, NULL, NULL);
            *dll_out = NULL;
            return status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t dll_deep_clone(const dll_t *src, dll_t **dll_out, void *ctx) {
    CCOL_CHECK_INIT(src);
    if (!dll_out) return CCOL_STATUS_INVALID_ARG;

    return dll_clone(src, dll_out, COPY_DEFAULT, ctx);
}

ccol_status_t dll_copy(dll_t *dest, const dll_t *src, free_func_t free_data, copy_func_t copy_data, void *ctx) {
    CCOL_CHECK_INIT(dest);
    CCOL_CHECK_INIT(src);
    
    if (!copy_data) return CCOL_STATUS_INVALID_ARG;

    dll_clear(dest, free_data, ctx);

    dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        void *data_copy = copy_data(curr->data, ctx);
        ccol_status_t status = dll_push_back(dest, data_copy);
        if (status != CCOL_STATUS_OK) {
        	dll_clear(dest, free_data, ctx);
            return status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t dll_deep_copy(dll_t *dest, const dll_t *src, free_func_t free_data, void *ctx) {
    return dll_copy(dest, src, free_data, COPY_DEFAULT, ctx);
}

// Cleanup
ccol_status_t dll_clear(dll_t *dll, free_func_t free_data, void *ctx) {
    CCOL_CHECK_INIT(dll); 

    dll_node_t *curr = dll->head;
    for (size_t i = 0; i < dll->size; i++) {
        dll_node_t *next = curr->next;
        dll_dispose_node(curr, free_data, ctx);
        curr = next;
    }

    dll->head = dll->tail = NULL;
    dll->size = 0;

    return CCOL_STATUS_OK;
}

ccol_status_t dll_destroy(dll_t *dll, free_func_t free_data, void *ctx) {
    CCOL_CHECK_INIT(dll);

    ccol_status_t status = dll_clear(dll, free_data, ctx);
    if (status != CCOL_STATUS_OK) return status;

    dll_uninit(dll);
    
    return CCOL_STATUS_OK;
}

ccol_status_t dll_free(dll_t **dll_ptr, free_func_t free_data, void *ctx) {
    if (!dll_ptr || !*dll_ptr || !(*dll_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = dll_destroy(*dll_ptr, free_data, ctx);
    free(*dll_ptr);
    *dll_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t dll_print(const dll_t *dll, print_func_t print_data, void *ctx) {
	CCOL_CHECK_INIT(dll);
    if (!print_data) return CCOL_STATUS_INVALID_ARG;
    if (dll->size == 0) {
    	printf("[]\n");
        return CCOL_STATUS_OK;
    }

    dll_node_t *curr = dll->head;

    printf("HEAD → [ ");
    for (size_t i = 0; i < dll->size; i++) {
    	print_data(curr->data, ctx);
        if (i != dll->size - 1) printf(" ] ⇄ [ ");
        curr = curr->next;
    }
    printf(" ] ← TAIL\n");
    return CCOL_STATUS_OK;
}
