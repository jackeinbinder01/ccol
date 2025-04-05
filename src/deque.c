/*
* deque.c / Practicum 1
*
* Jack Einbinder / CS5600 / Northeastern University
* Spring 2025 / March 19, 2025
*
*/

#include "../../include/data_structures/deque.h"
#include "../../include/components/message.h"
#include <stdlib.h>
#include <stdio.h>

deque_t* deque_init(void) { // uses cdll functions to implement a double ended queue
    deque_t* deque = malloc(sizeof(deque_t));
    if (!deque) {
        perror("ERROR: failed to initialize deque");
        return NULL;
    }

    deque->list = cdll_init();

    return deque;
}

void deque_destroy(deque_t* deque, void (*free_data)(void*)) {
    if (!deque) return;

    cdll_destroy(deque->list, free_data);

    free(deque);
    return;
}

int deque_push(deque_t* deque, void* data) {
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return -1;
    }

    return cdll_append(deque->list, data);
}

int deque_push_left(deque_t* deque, void* data) {
    if (!deque) {
        perror("ERROR: deque is NULL");
        return -1;
    }

    return cdll_prepend(deque->list, data);
}

void* deque_pop(deque_t* deque) {
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return NULL;
    }

    return cdll_pop(deque->list);
}

void* deque_pop_left(deque_t* deque) {
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return NULL;
    }

    return cdll_pop_left(deque->list);
}

int deque_delete(deque_t* deque, dll_node_t* node) {
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return -1;
    }
    if (!node) {
        fprintf(stderr, "ERROR: target node is NULL.\n");
        return -1;
    }

    return cdll_delete(deque->list, node);
}

dll_node_t* deque_search(const deque_t* deque, const void* data, int (*cmp)(const void*, const void*)) {
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return NULL;
    }

    return cdll_search(deque->list, data, cmp);
}

int deque_is_empty(deque_t* deque) {
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return -1;
    }

    return cdll_is_empty(deque->list);
}

size_t deque_size(deque_t* deque) {
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return (size_t)-1;
    }

    return cdll_size(deque->list);
}

void deque_print(deque_t* deque) { // used for testing
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return;
    }
    if (deque->list->size == 0) {
        printf("EMPTY - Deque.\n");
        printf("Deque = %zu\n", deque->list->size);
        return;
    }

    dll_node_t* curr = deque->list->head;
    do {
        message_t* curr_msg = (message_t*)curr->data;

        if (deque->list->size == 1) {
            printf("HEAD/TAIL: [msg_id: %lld]", curr_msg->id);
        } else if (curr == deque->list->head) {
            printf("HEAD: [msg_id: %lld] -> ", curr_msg->id);
        } else if (curr == deque->list->tail) {
            printf("[msg_id: %lld]: TAIL", curr_msg->id);
        } else {
            printf("[msg_id: %lld] -> ", curr_msg->id);
        }
        curr = curr->next;
    } while (curr != deque->list->head);

    printf("\n");
    printf("Deque size = %zu\n", deque->list->size);
    return;
}
