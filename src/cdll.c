/*
 * ccol/cdll.c
 *
 * Circular doubly-linked list
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "dll_internal.h"
#include "cdll.h"
#include "cdll_internal.h"
#include "ccol_status.h"
#include "ccol_macros.h"

// Create / Initialize
ccol_status_t cdll_init(cdll_t *cdll) {
    if (!cdll) return CCOL_STATUS_INVALID_ARG;

    cdll->head = NULL;
    cdll->tail = NULL;
    cdll->size = 0;
    cdll->is_initialized = true;

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_create(cdll_t **cdll_out) {
    if (!cdll_out) return CCOL_STATUS_INVALID_ARG;

    cdll_t* cdll = calloc(1, sizeof(cdll_t));
    if (!cdll) return CCOL_STATUS_ALLOC;

    ccol_status_t status = cdll_init(cdll);
    if (status != CCOL_STATUS_OK) {
        free(cdll);
        return status;
    }

    *cdll_out = cdll;
    return CCOL_STATUS_OK;
}

// Insertion
ccol_status_t cdll_push(cdll_t *cdll, void *data) {
    return cdll_push_back(cdll, data);
}

ccol_status_t cdll_push_front(cdll_t *cdll, void *data) {
    CCOL_CHECK_INIT(cdll);

    if (cdll->size == 0) return cdll_push_back(cdll, data);

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    new_node->data = data;

    new_node->next = cdll->head;
    new_node->prev = cdll->tail;
    cdll->head->prev = new_node;
    cdll->tail->next = new_node;
    cdll->head = new_node;

    cdll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t cdll_push_middle(cdll_t *cdll, void *data) {
    CCOL_CHECK_INIT(cdll);

    if (cdll->size == 0) return cdll_push_back(cdll, data);

    const dll_node_t *head = cdll->head;
    dll_node_t *middle = dll_get_middle_node(head, cdll->size);
    return cdll_insert_after(cdll, middle, data);
}

ccol_status_t cdll_push_back(cdll_t *cdll, void *data) {
    CCOL_CHECK_INIT(cdll);

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    new_node->data = data;

    if (cdll->size == 0) {
        new_node->next = new_node;
        new_node->prev = new_node;
        cdll->head = new_node;
        cdll->tail = new_node;
    } else {
        new_node->next = cdll->head;
        new_node->prev = cdll->tail;
        cdll->head->prev = new_node;
        cdll->tail->next = new_node;
        cdll->tail = new_node;
    }

    cdll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t cdll_insert_before(cdll_t *cdll, dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(cdll);
    if (!ref_node) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    if (ref_node == cdll->head) return cdll_push_front(cdll, data);

    new_node->data = data;
    new_node->next = ref_node;
    new_node->prev = ref_node->prev;

    ref_node->prev->next = new_node;
    ref_node->prev = new_node;

    cdll->head->prev = cdll->tail;
    cdll->tail->next = cdll->head;

    cdll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t cdll_insert_after(cdll_t *cdll, dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(cdll);
    if (!ref_node) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    if (ref_node == cdll->tail) return cdll_push_back(cdll, data);

    new_node->data = data;
    new_node->prev = ref_node;
    new_node->next = ref_node->next;

    ref_node->next->prev = new_node;
    ref_node->next = new_node;

    cdll->head->prev = cdll->tail;
    cdll->tail->next = cdll->head;

    cdll->size++;
    return CCOL_STATUS_OK;
}

// Removal
ccol_status_t cdll_pop(cdll_t *cdll, void **data_out) {
    return cdll_pop_back(cdll, data_out);
}

ccol_status_t cdll_pop_front(cdll_t *cdll, void **data_out) {
    CCOL_CHECK_INIT(cdll);
    if (!cdll->head) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *head = cdll->head;
    *data_out = head->data;

    return cdll_remove_node(cdll, head);
}

ccol_status_t cdll_pop_middle(cdll_t *cdll, void **data_out) {
    CCOL_CHECK_INIT(cdll);
    if (cdll->size == 0) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    if (cdll->size == 1) {
        return cdll_pop(cdll, data_out);
    }

    const dll_node_t *head = cdll->head;
    dll_node_t *middle = dll_get_middle_node(head, cdll->size);
    *data_out = middle->data;

    return cdll_remove_node(cdll, middle);
}

ccol_status_t cdll_pop_back(cdll_t *cdll, void **data_out) {
    CCOL_CHECK_INIT(cdll);
    if (!cdll->tail) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *tail = cdll->tail;
    *data_out = tail->data;

    return cdll_remove_node(cdll, tail);
}

ccol_status_t cdll_remove_node(cdll_t *cdll, dll_node_t* node) {
    CCOL_CHECK_INIT(cdll);
    if (cdll->size == 0) return CCOL_STATUS_EMPTY;
    if (!node) return CCOL_STATUS_INVALID_ARG;

    if (cdll->size == 1) {
        cdll->head = NULL;
        cdll->tail = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;

        if (node == cdll->head) cdll->head = node->next;
        if (node == cdll->tail) cdll->tail = node->prev;
    }

    free(node);
    cdll->size--;
    return CCOL_STATUS_OK;
}

ccol_status_t cdll_remove(cdll_t *cdll, void *data, int (*cmp)(const void *, const void *)) {
    CCOL_CHECK_INIT(cdll);

    dll_node_t *node = cdll_search(cdll, data, cmp);
    if (!node) return CCOL_STATUS_NOT_FOUND;

    return cdll_remove_node(cdll, node);
}

// Access
ccol_status_t cdll_get(const cdll_t *cdll, size_t index, void **data_out){
    CCOL_CHECK_INIT(cdll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (cdll->size == 0) return CCOL_STATUS_EMPTY;
    if (index > cdll->size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;

    dll_node_t *target;
    if (index < cdll->size / 2) {
        target = cdll->head;
        for (size_t i = 0; i < index; i++) {
            target = target->next;
        }
    } else {
        target = cdll->tail;
        for (size_t i = cdll->size - 1; i != index; i--) {
            target = target->prev;
        }
    }
    *data_out = target->data;

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_get_node(const cdll_t *cdll, size_t index, dll_node_t **node_out) {
    CCOL_CHECK_INIT(cdll);
    if (index > cdll->size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;
    if (!node_out) return CCOL_STATUS_INVALID_ARG;
    const dll_node_t *head = cdll->head;
    const dll_node_t *tail = cdll->tail;
    return dll_get_node_bounded(head, tail, cdll->size, index, node_out);
}

ccol_status_t cdll_peek(const cdll_t *cdll, void **data_out) {
    return cdll_peek_front(cdll, data_out);
}

ccol_status_t cdll_peek_front(const cdll_t *cdll, void **data_out) {
    CCOL_CHECK_INIT(cdll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (!cdll->head) return CCOL_STATUS_EMPTY;

    *data_out = cdll->head->data;

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_peek_middle(const cdll_t *cdll, void **data_out) {
    CCOL_CHECK_INIT(cdll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (cdll->size == 0) return CCOL_STATUS_EMPTY;

    const dll_node_t *head = cdll->head;
    dll_node_t *middle = dll_get_middle_node(head, cdll->size);
    *data_out = middle->data;

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_peek_back(const cdll_t *cdll, void **data_out) {
    CCOL_CHECK_INIT(cdll);
    if (!data_out) return CCOL_STATUS_INVALID_ARG;
    if (!cdll->tail) return CCOL_STATUS_EMPTY;

    *data_out = cdll->tail->data;

    return CCOL_STATUS_OK;
}

dll_node_t *cdll_search(const cdll_t *cdll, const void *data, int (*cmp)(const void *, const void *)) {
    if (!cdll || !cdll->is_initialized || cdll->size == 0 || !data || !cmp) return NULL;
    const dll_node_t *head = cdll->head;
    return dll_search_bounded(head, cdll->size, data, cmp);
}

// Attributes
bool cdll_is_empty(const cdll_t *cdll) {
    return (!cdll || !cdll->is_initialized || cdll->size == 0);
}

size_t cdll_size(const cdll_t *cdll) {
    if (!cdll || !cdll->is_initialized) return 0;
    return cdll->size;
}

bool cdll_contains(const cdll_t *cdll, const void *data, int (*cmp)(const void *, const void *)) {
    return cdll_search(cdll, data, cmp) != NULL;
}

bool cdll_contains_node(const cdll_t *cdll, const dll_node_t *node) {
    if (!cdll || !node) return false;
    for (dll_node_t *curr = cdll->head; curr; curr = curr->next) {
        if (curr == node) return true;
    }
    return false;
}

// Indexing
ccol_status_t cdll_safe_index_of(const cdll_t *cdll, void *data, int (*cmp)(const void *, const void *), size_t *out_index) {
    CCOL_CHECK_INIT(cdll);
    if (!cmp || !out_index) return CCOL_STATUS_INVALID_ARG;

    size_t index = 0;
    dll_node_t *curr = cdll->head;
    while (curr) {
        if (cmp(curr->data, data) == 0) {
            *out_index = index;
            return CCOL_STATUS_OK;
        }
        curr = curr->next;
        index++;
    }

    return CCOL_STATUS_NOT_FOUND;
}

size_t cdll_index_of(const cdll_t *cdll, void *data, int (*cmp)(const void *, const void *)) {
    size_t index;
    ccol_status_t status = cdll_safe_index_of(cdll, data, cmp, &index);
    if (status != CCOL_STATUS_OK) return CDLL_NOT_FOUND; // Return sentinal value if not found
    return index;
}

// Utilities
ccol_status_t cdll_set(cdll_t *cdll, size_t index, void *data) {
    CCOL_CHECK_INIT(cdll);
    if (cdll->size == 0) return CCOL_STATUS_EMPTY;
    if (index > cdll->size - 1) return CCOL_STATUS_OUT_OF_BOUNDS;

    dll_node_t *target;
    if (index < cdll->size / 2) {
        target = cdll->head;
        for (size_t i = 0; i < index; i++) {
            target = target->next;
        }
    } else {
        target = cdll->tail;
        for (size_t i = cdll->size - 1; i != index; i--) {
            target = target->prev;
        }
    }
    target->data = data;

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_swap_data(cdll_t *cdll, size_t i, size_t j) {
    CCOL_CHECK_INIT(cdll);
    if (cdll->size == 0) return CCOL_STATUS_EMPTY;
    if (i > cdll->size - 1 || j > cdll->size -1) return CCOL_STATUS_OUT_OF_BOUNDS;

    if (i == j) return CCOL_STATUS_OK;

    dll_node_t *node_i = NULL;
    dll_node_t *node_j = NULL;

    ccol_status_t status_get_i = cdll_get_node(cdll, i, &node_i);
    ccol_status_t status_get_j = cdll_get_node(cdll, j, &node_j);
    if (status_get_i != CCOL_STATUS_OK || status_get_j != CCOL_STATUS_OK) return CCOL_STATUS_OUT_OF_BOUNDS;

    void *tmp = node_i->data;
    node_i->data = node_j->data;
    node_j->data = tmp;

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_swap_nodes(cdll_t *cdll, dll_node_t *x, dll_node_t *y) {
    CCOL_CHECK_INIT(cdll);
    if (!x || !y) return CCOL_STATUS_INVALID_ARG;
    if (!cdll_contains_node(cdll, x) || !cdll_contains_node(cdll, y)) return CCOL_STATUS_INVALID_ARG;
    if (x == y) return CCOL_STATUS_OK;

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
    if (cdll->head == x) cdll->head = y;
    else if (cdll->head == y) cdll->head = x;

    if (cdll->tail == x) cdll->tail = y;
    else if (cdll->tail == y) cdll->tail = x;

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_reverse(cdll_t *cdll) {
    CCOL_CHECK_INIT(cdll);
    if (cdll->size == 0) return CCOL_STATUS_EMPTY;
    if (cdll->size == 1) return CCOL_STATUS_OK;

    dll_node_t *curr = cdll->head;
    for (size_t i = 0; i < cdll->size; i++) {
        SWAP_PTR(curr->next, curr->prev);
        curr = curr->prev;
    }

    return SWAP_PTR(cdll->head, cdll->tail);
}

// Copy / Clone
ccol_status_t cdll_clone(const cdll_t *src, cdll_t **cdll_out, void *(*copy_data)(const void *)) {
    CCOL_CHECK_INIT(src);
    if (!cdll_out || !copy_data) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = cdll_create(cdll_out);
    if (status != CCOL_STATUS_OK) return status;

    dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        void *data_copy = copy_data(curr->data);
        status = cdll_push_back(*cdll_out, data_copy);
        if (status != CCOL_STATUS_OK) {
            cdll_destroy(*cdll_out, NULL);
            *cdll_out = NULL;
            return status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_deep_clone(const cdll_t *src, cdll_t **cdll_out) {
    CCOL_CHECK_INIT(src);
    if (!cdll_out) return CCOL_STATUS_INVALID_ARG;

    return cdll_clone(src, cdll_out, COPY_DEFAULT);
}

ccol_status_t cdll_copy(cdll_t *dest, const cdll_t *src, void (*free_data)(void *), void *(*copy_data)(const void *)) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (!copy_data) return CCOL_STATUS_INVALID_ARG;

    cdll_clear(dest, free_data);

    dll_node_t *curr = src->head;
    for (size_t i = 0; i < src->size; i++) {
        void *data_copy = copy_data(curr->data);
        ccol_status_t status = cdll_push_back(dest, data_copy);
        if (status != CCOL_STATUS_OK) return status;
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t cdll_deep_copy(cdll_t *dest, const cdll_t *src, void (*free_data)(void *)) {
    return cdll_copy(dest, src, free_data, COPY_DEFAULT);
}

// Cleanup
void cdll_clear(cdll_t *cdll, void (*free_data)(void *)) {
    if (!cdll || !cdll->is_initialized) return;
    if (cdll->size == 0) return;

    dll_node_t *curr = cdll->head;

    for (size_t i = 0; i < cdll->size; i++) {
        dll_node_t *next = curr->next;
        dll_dispose_node(curr, free_data);
        curr = next;
    }

    cdll->head = NULL;
    cdll->tail = NULL;
    cdll->size = 0;
}

void cdll_destroy(cdll_t *cdll, void (*free_data)(void*)) {
    if (!cdll || !cdll->is_initialized) return;

    dll_node_t *curr = cdll->head;
    for (size_t i = 0; i < cdll->size; i++) {
        dll_node_t *next = curr->next;
        dll_dispose_node(curr, free_data);
        curr = next;
    }
    free(cdll);
}

void cdll_free(cdll_t *cdll) {
    if (!cdll || !cdll->is_initialized) return;

    cdll_uninit(cdll);
    free(cdll);
}

// Print / Debug
ccol_status_t cdll_print(const cdll_t *cdll, void (*print_data)(const void *)) {
	CCOL_CHECK_INIT(cdll);
    if (!print_data) return CCOL_STATUS_INVALID_ARG;
    if (cdll->size == 0) {
    	printf("[]\n");
        return CCOL_STATUS_OK;
    }

    dll_node_t *curr = cdll->head;

    printf("HEAD → [");
    for (size_t i = 0; i < cdll->size; i++) {
    	print_data(curr->data);
        if (i != cdll->size - 1) printf("] ⇄ [");
        curr = curr->next;
    }
    printf("] ← TAIL\n");
    return CCOL_STATUS_OK;
}
