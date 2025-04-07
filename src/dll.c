/*
 * ccol/dll.h
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
#include "ccol_status.h"
#include "ccol_macros.h"

// Private
static dll_node_t *dll_get_middle_node(const dll_t *dll) {
    if (!dll || !dll->is_initialized || dll->size == 0) return NULL;

    dll_node_t *slow = dll->head;
    dll_node_t *fast = dll->head;

    while (fast && fast->next && fast != dll->head) {
      slow = slow->next;
      fast = fast->next->next;
    }

    return slow;
}

static void dll_uninit(dll_t *dll) {
    if (!dll || !dll->is_initialized) return;

    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    dll->is_initialized = false;
}

// Iterator
typedef struct {
    const dll_t *dll;
    dll_node_t *current;
} dll_iterator_state_t;

static bool dll_has_next(iterator_t *iter) {
    if (!iter || !iter->state) return false;
    dll_iterator_state_t *state = iter->state;
    return state->current != NULL;
}

static void *dll_next(iterator_t *iter) {
    if (!iter || !iter->state) return false;
    dll_iterator_state_t *state = iter->state;
    if (!state->current) return NULL;

    void *data = state->current->data;
    state->current = state->current->next;
    return data;
}

static void dll_iterator_destroy(iterator_t *iter) {
    if (iter) {
        free(iter->state);
        free(iter);
    }
}

// Create / Initialize
ccol_status_t dll_init(dll_t *dll) {
    if (!dll) return CCOL_STATUS_INVALID_ARG;

    dll->head = NULL;
    dll->tail = NULL;
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

    dll_node_t *middle = dll_get_middle_node(dll);
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

    new_node->data = data;

    new_node->next = ref_node->next;
    new_node->prev = ref_node;
    ref_node->next = new_node;

    if (!new_node->next) dll->tail = new_node;
    else new_node->next->prev = new_node;

    dll->size++;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_insert_after(dll_t *dll, dll_node_t* ref_node, void *data) {
    CCOL_CHECK_INIT(dll);
    if (!ref_node) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node) return CCOL_STATUS_ALLOC;

    new_node->data = data;

    new_node->next = ref_node;
    new_node->prev = ref_node->prev;

    if (!ref_node->prev) dll->head = new_node;
    else ref_node->prev->next = new_node;

    ref_node->prev = new_node;

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

    return dll_remove_node(dll, head);
}

ccol_status_t dll_pop_middle(dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    if (dll->size == 1) {
        return dll_pop(dll, data_out);
    }

    dll_node_t *middle = dll_get_middle_node(dll);
    *data_out = middle->data;

    return dll_remove_node(dll, middle);
}

ccol_status_t dll_pop_back(dll_t *dll, void **data_out) {
    CCOL_CHECK_INIT(dll);
    if (!dll->tail) return CCOL_STATUS_EMPTY;
    if (!data_out) return CCOL_STATUS_INVALID_ARG;

    dll_node_t *tail = dll->tail;
    *data_out = tail->data;

    return dll_remove_node(dll, tail);
}

ccol_status_t dll_remove_node(dll_t *dll, dll_node_t* node) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (!node) return CCOL_STATUS_INVALID_ARG;

    if (node->prev) node->prev->next = node->next;
    else dll->head = node->next;

    if (!node->next) dll->tail = node->prev;
    else node->next->prev = node->prev;

    free(node);
    dll->size--;
    return CCOL_STATUS_OK;
}

ccol_status_t dll_remove(dll_t *dll, void *data, int (*cmp)(const void *, const void *)) {
    CCOL_CHECK_INIT(dll);

    dll_node_t *node = dll_search(dll, data, cmp);
    if (!node) return CCOL_STATUS_NOT_FOUND;

    return dll_remove_node(dll, node);
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
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (index >= dll->size) return CCOL_STATUS_OUT_OF_BOUNDS;

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
    *node_out = target;

    return CCOL_STATUS_OK;
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

    dll_node_t *middle = dll_get_middle_node(dll);
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

dll_node_t *dll_search(const dll_t *dll, const void *data, int (*cmp)(const void *, const void *)) {
    if (!dll || !dll-> is_initialized || dll->size == 0 || !data || !cmp) return NULL;

    dll_node_t *curr = dll->head;
    while (curr) {
        if (cmp(curr->data, data) == 0) return curr;
        curr = curr->next;
    }

    return NULL;
}

// Attributes
bool dll_is_empty(const dll_t *dll) {
    return (!dll || !dll->is_initialized || dll->size == 0);
}

size_t dll_size(const dll_t *dll) {
    if (!dll || !dll->is_initialized) return 0;
    return dll->size;
}

bool dll_contains(const dll_t *dll, const void *data, int (*cmp)(const void *, const void *)) {
    return dll_search(dll, data, cmp) != NULL;
}

bool dll_contains_node(const dll_t *dll, const dll_node_t *node) {
    if (!dll || !node) return false;
    for (dll_node_t *curr = dll->head; curr; curr = curr->next) {
        if (curr == node) return true;
    }
    return false;
}

// Indexing
ccol_status_t dll_safe_index_of(const dll_t *dll, void *data, int (*cmp)(const void *, const void *), size_t *out_index) {
    CCOL_CHECK_INIT(dll);
    if (!cmp || !out_index) return CCOL_STATUS_INVALID_ARG;

    size_t index = 0;
    dll_node_t *curr = dll->head;
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

size_t dll_index_of(const dll_t *dll, void *data, int (*cmp)(const void *, const void *)) {
    size_t index;
    ccol_status_t status = dll_safe_index_of(dll, data, cmp, &index);
    if (status != CCOL_STATUS_OK) return DLL_NOT_FOUND; // Return sentinal value if not found
    return index;
}

// Utilities
ccol_status_t dll_set(dll_t *dll, size_t index, void *data) {
    CCOL_CHECK_INIT(dll);
    if (dll->size == 0) return CCOL_STATUS_EMPTY;
    if (index >= dll->size) return CCOL_STATUS_OUT_OF_BOUNDS;

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
    if (i >= dll->size || j >= dll->size) return CCOL_STATUS_OUT_OF_BOUNDS;

    if (i == j) return CCOL_STATUS_OK;

    dll_node_t *node_i = NULL;
    dll_node_t *node_j = NULL;

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
    while (curr) {
      SWAP_PTR(curr->next, curr->prev);
      curr = curr->prev;
    }

    return SWAP_PTR(dll->head, dll->tail);
}

// Copy / Clone
ccol_status_t dll_clone(const dll_t *src, dll_t **dll_out, void *(*copy_data)(const void *)) {
    CCOL_CHECK_INIT(src);
    if (!dll_out || !copy_data) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = dll_create(dll_out);
    if (status != CCOL_STATUS_OK) return status;

    dll_node_t *curr = src->head;
    while (curr) {
        void *data_copy = copy_data(curr->data);
        status = dll_push_back(*dll_out, data_copy);
        if (status != CCOL_STATUS_OK) {
            dll_destroy(*dll_out, NULL);
            *dll_out = NULL;
            return status;
        }
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t dll_deep_clone(const dll_t *src, dll_t **dll_out) {
    CCOL_CHECK_INIT(src);
    if (!dll_out) return CCOL_STATUS_INVALID_ARG;

    return dll_clone(src, dll_out, COPY_DEFAULT);
}

ccol_status_t dll_copy(dll_t *dest, const dll_t *src, void (*free_data)(void *), void *(*copy_data)(const void *)) {
    CCOL_CHECK_INIT(src);
    CCOL_CHECK_INIT(dest);
    if (!copy_data) return CCOL_STATUS_INVALID_ARG;

    dll_clear(dest, free_data);

    dll_node_t *curr = src->head;
    while (curr) {
        void *data_copy = copy_data(curr->data);
        ccol_status_t status = dll_push_back(dest, data_copy);
        if (status != CCOL_STATUS_OK) return status;
        curr = curr->next;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t dll_deep_copy(dll_t *dest, const dll_t *src, void (*free_data)(void *)) {
    return dll_copy(dest, src, free_data, COPY_DEFAULT);
}

// Cleanup
void dll_clear(dll_t *dll, void (*free_data)(void *)) {
    if (!dll || !dll->is_initialized) return;
    if (dll->size == 0) return;

    dll_node_t *curr = dll->head;
    while (curr) {
        dll_node_t *next = curr->next;
        dll_dispose_node(curr, free_data);
        curr = next;
    }

    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
}

void dll_destroy(dll_t *dll, void (*free_data)(void*)) {
    if (!dll || !dll->is_initialized) return;

    dll_node_t *curr = dll->head;
    while (curr) {
        dll_node_t *next = curr->next;
        dll_dispose_node(curr, free_data);
        curr = next;
    }
    free(dll);
}

void dll_free(dll_t *dll) {
    if (!dll || !dll->is_initialized) return;

    dll_uninit(dll);
    free(dll);
}

void dll_free_node(dll_node_t *node) {
    if (!node) return;

    if (node->data) free(node->data);
    node->data = NULL;
    node->next = NULL;
    node->prev = NULL;
    free(node);
}

void dll_dispose_node(dll_node_t *node, void (*free_data)(void *)) {
    if (!node) return;
    if (free_data && node->data) free_data(node->data);
    dll_free_node(node);
}

// Iterate
iterator_t *dll_iterator_create(const dll_t *dll) {
    if (!dll || !dll->is_initialized) return NULL;

    dll_iterator_state_t *state = calloc(1, sizeof(dll_iterator_state_t));
    if (!state) return NULL;

    iterator_t *iter = calloc(1, sizeof(iterator_t));
    if (!iter) {
        free(state);
        return NULL;
    }

    state->dll = dll;
    state->current = dll->head;

    iter->container = (void *)dll;
    iter->state = state;
    iter->has_next = dll_has_next;
    iter->next = dll_next;
    iter->destroy = dll_iterator_destroy;

    return iter;
}

// Print / Debug
ccol_status_t dll_print(const dll_t *dll, void (*print_data)(const void *)) {
	CCOL_CHECK_INIT(dll);
    if (!print_data) return CCOL_STATUS_INVALID_ARG;
    if (dll->size == 0) {
    	printf("[]\n");
        return CCOL_STATUS_OK;
    }

    dll_node_t *curr = dll->head;

    printf("HEAD → [");
    for (size_t i = 0; i < dll->size; i++) {
    	print_data(curr->data);
        if (i != dll->size - 1) printf("] ⇄ [");
        curr = curr->next;
    }
    printf("] ← TAIL\n");
    return CCOL_STATUS_OK;
}
