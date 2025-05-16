/*
 * ccol/src/dll/ccol_dll.c
 *
 * Doubly-linked list (dll) implementation.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ccol/ccol_dll.h"
#include "ccol/ccol_status.h"
#include "ccol/ccol_macros.h"
#include "ccol/ccol_constants.h"

#include "../dll/internal.h"

// Create / Initialize
ccol_status_t ccol_dll_init(
    ccol_dll_t *dll,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
) {
    if (!dll) return CCOL_STATUS_INVALID_ARG;

    dll->head = dll->tail = NULL;
    dll->size = 0;

    dll->copier = copier;
    dll->freer = freer;
    dll->printer = printer;
    dll->comparator = comparator;

    dll->is_initialized = true;

    return CCOL_STATUS_OK;
}

ccol_status_t ccol_dll_create(
    ccol_dll_t **dll_out,
    ccol_copy_t copier,
    ccol_free_t freer,
    ccol_print_t printer,
    ccol_comparator_t comparator
) {
    if (!dll_out) return CCOL_STATUS_INVALID_ARG;

    *dll_out = NULL;

    ccol_dll_t *dll = calloc(1, sizeof(ccol_dll_t));
    if (!dll) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_dll_init(dll, copier, freer, printer, comparator);
    if (status != CCOL_STATUS_OK) {
        free(dll);
        return status;
    }

    *dll_out = dll;
    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t ccol_dll_push(ccol_dll_t *dll, void *data) {
    return ccol_dll_push_back(dll, data);
}

ccol_status_t ccol_dll_push_front(ccol_dll_t *dll, void *data) {
    CCOL_CHECK_INIT(dll);

    ccol_dll_node_t *new_node = malloc(sizeof(ccol_dll_node_t));
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

ccol_status_t ccol_dll_push_middle(ccol_dll_t *dll, void *data) {
    CCOL_CHECK_INIT(dll);

    if (dll->size == 0) return ccol_dll_push_back(dll, data);

    const ccol_dll_node_t *head = dll->head;
    ccol_dll_node_t *middle = ccol__dll_get_middle_node(head, dll->size);
    return ccol_dll_insert_after(dll, middle, data);
}

ccol_status_t ccol_dll_push_back(ccol_dll_t *dll, void *data) {
    CCOL_CHECK_INIT(dll);

    ccol_dll_node_t *new_node = malloc(sizeof(ccol_dll_node_t));
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

ccol_status_t ccol_dll_insert_before(ccol_dll_t *dll, ccol_dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(dll);
    if (!ref_node) return CCOL_STATUS_INVALID_ARG;

    ccol_dll_node_t *new_node = malloc(sizeof(ccol_dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    if (ref_node == dll->head) return ccol_dll_push_front(dll, data);

    new_node->data = data;
    new_node->next = ref_node;
    new_node->prev = ref_node->prev;

    ref_node->prev->next = new_node;
    ref_node->prev = new_node;

    dll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_dll_insert_after(ccol_dll_t *dll, ccol_dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(dll);
    if (!ref_node) return CCOL_STATUS_INVALID_ARG;

    ccol_dll_node_t *new_node = malloc(sizeof(ccol_dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    if (ref_node == dll->tail) return ccol_dll_push_back(dll, data);

    new_node->data = data;
    new_node->prev = ref_node;
    new_node->next = ref_node->next;

    ref_node->next->prev = new_node;
    ref_node->next = new_node;

    dll->size++;
    return CCOL_STATUS_OK;
}

// Removal
ccol_status_t ccol_dll_pop(ccol_dll_t *dll, void **data_out) {
    return ccol_dll_pop_back(dll, data_out);
}

ccol_status_t ccol_dll_pop_front(ccol_dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!dll->head) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    ccol_dll_node_t *head = dll->head;
    *data_out = head->data;

    return ccol_dll_remove_node(dll, head);
}

ccol_status_t ccol_dll_pop_middle(ccol_dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    if (dll->size == 1) {
        return ccol_dll_pop(dll, data_out);
    }

    const ccol_dll_node_t *head = dll->head;
    ccol_dll_node_t *middle = ccol__dll_get_middle_node(head, dll->size);
    *data_out = middle->data;

    return ccol_dll_remove_node(dll, middle);
}

ccol_status_t ccol_dll_pop_back(ccol_dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!dll->tail) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    *data_out = NULL;

    ccol_dll_node_t *tail = dll->tail;
    *data_out = tail->data;

    return ccol_dll_remove_node(dll, tail);
}

ccol_status_t ccol_dll_remove_node(ccol_dll_t *dll, ccol_dll_node_t* node) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (!node) return CCOL_STATUS_INVALID_ARG;

    if (node->prev) node->prev->next = node->next;
    else dll->head = node->next;

    if (!node->next) dll->tail = node->prev;
    else node->next->prev = node->prev;

    ccol__dll_dispose_node(dll, node);
    dll->size--;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_dll_remove(ccol_dll_t *dll, void *data) {
    CCOL_CHECK_INIT(dll);

    ccol_dll_node_t *node = ccol_dll_search(dll, data);
    if (!node) return CCOL_STATUS_NOT_FOUND;

    return ccol_dll_remove_node(dll, node);
}

// Access
ccol_status_t ccol_dll_get(const ccol_dll_t *dll, size_t index, void **data_out){
    CCOL_CHECK_INIT(dll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (index > dll->size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;

    *data_out = NULL;

    ccol_dll_node_t *target;
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

ccol_status_t ccol_dll_get_node(const ccol_dll_t *dll, size_t index, ccol_dll_node_t **node_out) {
    CCOL_CHECK_INIT(dll);
    if (!node_out) return CCOL_STATUS_INVALID_ARG;
    if (index > dll->size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;

    return ccol__dll_get_node_bounded(dll->head, dll->tail, dll->size, index, node_out);
}

ccol_status_t ccol_dll_peek(const ccol_dll_t *dll, void **data_out) {
    return ccol_dll_peek_front(dll, data_out);
}

ccol_status_t ccol_dll_peek_front(const ccol_dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (!dll->head) return CCOL_STATUS_EMPTY;

    *data_out = dll->head->data;

    return CCOL_STATUS_OK;
}

ccol_status_t ccol_dll_peek_middle(const ccol_dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (dll->size == 0) return CCOL_STATUS_EMPTY;

    *data_out = NULL;

    const ccol_dll_node_t *head = dll->head;
    ccol_dll_node_t *middle = ccol__dll_get_middle_node(head, dll->size);
    *data_out = middle->data;

    return CCOL_STATUS_OK;
}

ccol_status_t ccol_dll_peek_back(const ccol_dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (!dll->tail) return CCOL_STATUS_EMPTY;

    *data_out = dll->tail->data;

    return CCOL_STATUS_OK;
}

ccol_dll_node_t *dll_search(const ccol_dll_t *dll, const void *data) {
    if (!dll || !dll->is_initialized || !dll->comparator.func || dll->size == 0 || !data) return NULL;
    return ccol__dll_search_bounded(dll, dll->head, dll->size, data);
}

// Attributes
bool dll_is_empty(const ccol_dll_t *dll) {
    return (!dll || !dll->is_initialized || dll->size == 0);
}

size_t dll_size(const ccol_dll_t *dll) {
    if (!dll || !dll->is_initialized) return 0;
    return dll->size;
}

bool dll_contains(const ccol_dll_t *dll, const void *data) {
    return dll_search(dll, data) != NULL;
}

bool ccol_dll_contains_node(const ccol_dll_t *dll, const ccol_dll_node_t *node) {
    if (!dll || !node) return false;

    ccol_dll_node_t *curr = dll->head;
    for (size_t i = 0; i < dll->size; i++, curr = curr->next) {
        if (curr == node) return true;
    }
    return false;
}

// Indexing
ccol_status_t ccol_dll_safe_index_of(const ccol_dll_t *dll, void *data, size_t *out_index) {
    CCOL_CHECK_INIT(dll);
    if (!out_index) return CCOL_STATUS_INVALID_ARG;
    if (!dll->comparator.func) return CCOL_STATUS_COMPARATOR_FUNC;

    ccol_dll_node_t *curr = dll->head;
    for (size_t i = 0; i < dll->size; i++) {
        if (dll->comparator.func(curr->data, data, dll->comparator.ctx) == 0) {
            *out_index = i;
            return CCOL_STATUS_OK;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_NOT_FOUND;
}

size_t dll_index_of(const ccol_dll_t *dll, void *data) {
    size_t index;
    ccol_status_t status = ccol_dll_safe_index_of(dll, data, &index);
    if (status != CCOL_STATUS_OK) return CCOL_DLL_INDEX_NOT_FOUND;
    return index;
}

// Utilities
ccol_status_t ccol_dll_set(ccol_dll_t *dll, size_t index, void *data) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (index > dll->size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;

    ccol_dll_node_t *target;
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

ccol_status_t ccol_dll_swap_data(ccol_dll_t *dll, size_t i, size_t j) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (i > dll->size - 1 || j > dll->size -1) return CCOL_STATUS_OUT_OF_BOUNDS;

    if (i == j) return CCOL_STATUS_OK;

    ccol_dll_node_t *node_i = NULL, *node_j = NULL;

    ccol_status_t status_get_i = ccol_dll_get_node(dll, i, &node_i);
    ccol_status_t status_get_j = ccol_dll_get_node(dll, j, &node_j);
    if (status_get_i != CCOL_STATUS_OK || status_get_j != CCOL_STATUS_OK) return CCOL_STATUS_OUT_OF_BOUNDS;

    void *tmp = node_i->data;
    node_i->data = node_j->data;
    node_j->data = tmp;

    return CCOL_STATUS_OK;
}

ccol_status_t ccol_dll_swap_nodes(ccol_dll_t *dll, ccol_dll_node_t *x, ccol_dll_node_t *y) {
    CCOL_CHECK_INIT(dll);
    if (!x || !y) return CCOL_STATUS_INVALID_ARG;
    if (!ccol_dll_contains_node(dll, x) || !ccol_dll_contains_node(dll, y)) return CCOL_STATUS_INVALID_ARG;
    if (x == y || dll->size < 2) return CCOL_STATUS_OK;

    // Handle adjacent nodes
    if (x->next == y || y->next == x) {
        if (y->next == x) { // makes sure x comes first
            ccol_dll_node_t *tmp = x;
            x = y;
            y = tmp;
        }
        ccol_dll_node_t *x_prev = x->prev;
        ccol_dll_node_t *y_next = y->next;

        if (x_prev) x_prev->next = y;
        if (y_next) y_next->prev = x;

        y->prev = x_prev;
        x->next = y_next;
        y->next = x;
        x->prev = y;
    } else { // Handle non-adjacent nodes
        ccol_dll_node_t *x_prev = x->prev, *x_next = x->next;
        ccol_dll_node_t *y_prev = y->prev, *y_next = y->next;

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

ccol_status_t ccol_dll_reverse(ccol_dll_t *dll) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (dll->size == 1) return CCOL_STATUS_OK;

    ccol_dll_node_t *curr = dll->head;
    for (size_t i = 0; i < dll->size; i++) {
      CCOL_SWAP_PTR(curr->next, curr->prev);
      curr = curr->prev;
    }

    return CCOL_SWAP_PTR(dll->head, dll->tail);
}

// Copy / Clone
ccol_status_t ccol_dll_clone(const ccol_dll_t *src, ccol_dll_t **dll_out) {
    return ccol_dll_deep_clone(src, dll_out);
}

ccol_status_t ccol_dll_deep_clone(const ccol_dll_t *src, ccol_dll_t **dll_out) {
    CCOL_CHECK_INIT(src);
    if (!dll_out) return CCOL_STATUS_INVALID_ARG;
    if (!src->copier.func) return CCOL_STATUS_COPY_FUNC;

    *dll_out = NULL;

    ccol_status_t status = ccol_dll_create(dll_out, src->copier, src->freer, src->printer, src->comparator);
    if (status != CCOL_STATUS_OK) return status;

    ccol_dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        void *data_copy = src->copier.func(curr->data, src->copier.ctx);
        if (!data_copy && curr->data != NULL) {
            ccol_dll_destroy(*dll_out);
            *dll_out = NULL;
            return CCOL_STATUS_COPY;
        }

        status = ccol_dll_push_back(*dll_out, data_copy);
        if (status != CCOL_STATUS_OK) {
            if (src->freer.func && data_copy) src->freer.func(data_copy, src->freer.ctx);
            ccol_dll_destroy(*dll_out);
            *dll_out = NULL;
            return status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t ccol_dll_shallow_clone(const ccol_dll_t *src, ccol_dll_t **dll_out) {
    CCOL_CHECK_INIT(src);
    if (!dll_out) return CCOL_STATUS_INVALID_ARG;

    *dll_out = NULL;

    ccol_dll_t *clone = calloc(1, sizeof(ccol_dll_t));
    if (!clone) return CCOL_STATUS_ALLOC;

    ccol_status_t status = ccol_dll_init(
        clone,
        src->copier,
        src->freer,
        src->printer,
        src->comparator
    );
    if (status != CCOL_STATUS_OK) {
        free(clone);
        return status;
    }

    ccol_dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        status = ccol_dll_push_back(clone, curr->data);
        if (status != CCOL_STATUS_OK) {
            ccol_dll_node_t *node = clone->head;
            for (size_t j = 0; j < clone->size; j++) {
                ccol_dll_node_t *next = node->next;
                free(node);
                node = next;
            }
            free(clone);
            *dll_out = NULL;
            return status;
        }
        curr = curr->next;
    }

    *dll_out = clone;
    return CCOL_STATUS_OK;
}

ccol_status_t ccol_dll_copy(ccol_dll_t *dest, const ccol_dll_t *src) {
    return ccol_dll_deep_copy(dest, src);
}

ccol_status_t ccol_dll_deep_copy(ccol_dll_t *dest, const ccol_dll_t *src) {
    CCOL_CHECK_INIT(dest);
    CCOL_CHECK_INIT(src);
    if (!src->copier.func) return CCOL_STATUS_COPY_FUNC;
    if (dest == src) return CCOL_STATUS_OK;

    ccol_status_t status = ccol_dll_clear(dest);
    if (status != CCOL_STATUS_OK) return status;

    dest->copier = src->copier;
    dest->freer = src->freer;
    dest->printer = src->printer;
    dest->comparator = src->comparator;

    ccol_dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        void *data_copy = src->copier.func(curr->data, src->copier.ctx);
        if (!data_copy && curr->data != NULL) {
            status = ccol_dll_clear(dest);
            return status != CCOL_STATUS_OK ? status: CCOL_STATUS_COPY;
        }

        status = ccol_dll_push_back(dest, data_copy);
        if (status != CCOL_STATUS_OK) {
            if (src->freer.func && data_copy) src->freer.func(data_copy, src->freer.ctx);
            ccol_status_t clear_status = ccol_dll_clear(dest);
            return clear_status != CCOL_STATUS_OK ? clear_status: status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t ccol_dll_shallow_copy(ccol_dll_t *dest, const ccol_dll_t *src) {
    CCOL_CHECK_INIT(dest);
    CCOL_CHECK_INIT(src);
    if (dest == src) return CCOL_STATUS_OK;

    dest->copier = src->copier;
    dest->freer = src->freer;
    dest->printer = src->printer;
    dest->comparator = src->comparator;

    ccol_dll_node_t *node = dest->head;
    for (size_t i = 0; i < dest->size; i++) {
        ccol_dll_node_t *next = node->next;
        free(node);
        node = next;
    }
    dest->head = dest->tail = NULL;
    dest->size = 0;

    ccol_dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        ccol_status_t status = ccol_dll_push_back(dest, curr->data);
        if (status != CCOL_STATUS_OK) {
            ccol_dll_node_t *node = dest->head;
            for (size_t j = 0; j < dest->size; j++) {
                ccol_dll_node_t *next = node->next;
                free(node);
                node = next;
            }
            dest->head = dest->tail = NULL;
            dest->size = 0;
            return status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

// Cleanup
ccol_status_t ccol_dll_clear(ccol_dll_t *dll) {
    CCOL_CHECK_INIT(dll); 

    ccol_dll_node_t *curr = dll->head;
    for (size_t i = 0; i < dll->size; i++) {
        ccol_dll_node_t *next = curr->next;
        ccol__dll_dispose_node(dll, curr);
        curr = next;
    }

    dll->head = dll->tail = NULL;
    dll->size = 0;

    return CCOL_STATUS_OK;
}

ccol_status_t ccol_dll_destroy(ccol_dll_t *dll) {
    CCOL_CHECK_INIT(dll);

    ccol_status_t status = ccol_dll_clear(dll);
    if (status != CCOL_STATUS_OK) return status;

    return ccol__dll_uninit(dll);
}

ccol_status_t ccol_dll_free(ccol_dll_t **dll_ptr) {
    if (!dll_ptr || !*dll_ptr || !(*dll_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = ccol_dll_destroy(*dll_ptr);
    free(*dll_ptr);
    *dll_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t ccol_dll_print(const ccol_dll_t *dll) {
	CCOL_CHECK_INIT(dll);
    if (!dll->printer.func) return CCOL_STATUS_PRINT_FUNC;
    if (dll->size == 0) {
    	printf("[]\n");
        return CCOL_STATUS_EMPTY;
    }

    ccol_dll_node_t *curr = dll->head;

    printf("HEAD → [ ");
    for (size_t i = 0; i < dll->size; i++) {
    	dll->printer.func(curr->data, dll->printer.ctx);
        if (i != dll->size - 1) printf(" ] ⇄ [ ");
        curr = curr->next;
    }
    printf(" ] ← TAIL\n");
    
    return CCOL_STATUS_OK;
}
