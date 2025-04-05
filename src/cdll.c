/*
* cdll.c / Practicum 1
*
* Jack Einbinder / CS5600 / Northeastern University
* Spring 2025 / March 19, 2025
*
*/

#include "../../include/data_structures/cdll.h"
#include "../../include/components/message.h"
#include <stdlib.h>
#include <stdio.h>

cdll_t* cdll_init(void) {
    cdll_t* cdll = malloc(sizeof(cdll_t));
    if (!cdll) {
      perror("ERROR: failed to initialize circular doubly linked list");
      return NULL;
    }

    cdll->head = NULL;
    cdll->tail = NULL;
    cdll->size = 0;

    return cdll;
}

void cdll_destroy(cdll_t* cdll, void (*free_data)(void*)) {
    if (!cdll) return;
    if (!cdll->head) {
        free(cdll);
        return;
    }

    dll_node_t* curr = cdll->head;

    // free data in each node
    do {
        dll_node_t* next = curr->next;
        if (free_data) {
            free_data(curr->data);
        }
        free(curr);
        curr = next;
    } while (curr != cdll->head);

    free(cdll);
    return;
}

int cdll_prepend(cdll_t* cdll, void* data) {
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return -1;
    }

    dll_node_t* new_node = malloc(sizeof(dll_node_t));
    if (!new_node) {
        perror("ERROR: failed to create new doubly linked node");
        return -1;
    }

    new_node->data = data;

    if (cdll->head) { // cdll is not empty
        new_node->next = cdll->head;
        new_node->prev = cdll->tail;
        cdll->head->prev = new_node;
        cdll->tail->next = new_node;
    } else { // cdll is empty
        new_node->next = new_node;
        new_node->prev = new_node;
        cdll->tail = new_node;
    }

    cdll->head = new_node;
    cdll->size++;
    return 0;
}

int cdll_append(cdll_t* cdll, void* data) {
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return -1;
    }

    dll_node_t* new_node = malloc(sizeof(dll_node_t));
    if (!new_node) {
        perror("ERROR: failed to create new doubly linked list node");
        return -1;
    }

    new_node->data = data;

    if (cdll->tail) { // cdll is not empty
        new_node->next = cdll->head;
        new_node->prev = cdll->tail;
        cdll->head->prev = new_node;
        cdll->tail->next = new_node;
    } else { // cdll is empty
        new_node->next = new_node;
        new_node->prev = new_node;
        cdll->head = new_node;
    }

    cdll->tail = new_node;
    cdll->size++;
    return 0;
}

int cdll_insert_after(cdll_t* cdll, dll_node_t* target_node, void* data) {
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return -1;
    }
    if (!target_node) {
        fprintf(stderr, "ERROR: target node is NULL.\n");
        return -1;
    }
    dll_node_t* new_node = malloc(sizeof(dll_node_t));
    if (!new_node) {
        perror("ERROR: failed to create new doubly linked node");
        return -1;
    }

    new_node->data = data;

    if (!cdll->head) { // cdll is empty
        new_node->next = new_node;
        new_node->prev = new_node;
        cdll->head = new_node;
        cdll->tail = new_node;
    } else { // cdll is not empty
        new_node->next = target_node->next;
        new_node->prev = target_node;
        target_node->next = new_node;

        if (target_node == cdll->tail) { // inserted node is new tail
            cdll->tail = new_node;
        } else {
            new_node->next->prev = new_node;
        }
    }
    cdll->size++;
    return 0;
}

int cdll_insert_before(cdll_t* cdll, dll_node_t* target_node, void* data) {
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return -1;
    }
    if (!target_node) {
        fprintf(stderr, "ERROR: target node is NULL.\n");
        return -1;
    }

    dll_node_t* new_node = malloc(sizeof(dll_node_t));
    if (!new_node) {
        perror("ERROR: failed to create new doubly linked node");
        return -1;
    }

    new_node->data = data;

    if (!cdll->head) { // list is empty
        new_node->next = new_node;
        new_node->prev = new_node;
        cdll->head = new_node;
        cdll->tail = new_node;
    } else { // insert new node before target node
        new_node->next = target_node;
        new_node->prev = target_node->prev;
        target_node->prev = new_node;

        if (target_node == cdll->head) { // if target is head
            cdll->head = new_node; // new node becomes head
        } else {
            new_node->next->prev = new_node; // link new node's successor
        }
    }
    cdll->size++;
    return 0;
}

int cdll_delete(cdll_t* cdll, dll_node_t* target_node) {
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return -1;
    }
    if (!target_node) {
        fprintf(stderr, "ERROR: target node is NULL.\n");
        return -1;
    }

    message_t* message = target_node->data;

    dll_node_t* delete_node = cdll_search(cdll, message, message_cmp_id);
    if (!delete_node) {
        fprintf(stderr, "ERROR: Could not find target node in cdll.\n");
        return -1;
    }

    if (cdll->size == 1) { // delete only node
        cdll->head = NULL;
        cdll->tail = NULL;
    } else if (delete_node == cdll->head) { // delete head node
        cdll->head = cdll->head->next;
        cdll->head->prev = cdll->tail;
        cdll->tail->next = cdll->head;
    } else if (delete_node == cdll->tail) { // delete tail node
        cdll->tail = delete_node->prev;
        cdll->tail->next = cdll->head;
        cdll->head->prev = cdll->tail;
    } else { // delete internal node
      delete_node->prev->next = delete_node->next;
      delete_node->next->prev = delete_node->prev;
    }

    free(delete_node);
    cdll->size--;
    return 0;
}

dll_node_t* cdll_search(const cdll_t* cdll, const void* data, int (*cmp)(const void*, const void*)) {
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return NULL;
    }
    if (!cdll->head) {
        fprintf(stderr, "ERROR: circular doubly linked list is empty.\n");
        return NULL;
    }
    if (!cmp) {
        fprintf(stderr, "ERROR: comparator is NULL.\n");
        return NULL;
    }

    // search list for target node using passed comparator
    dll_node_t* curr = cdll->head;
    do {
        if (cmp(curr->data, data) == 0) {
            return curr;
        } else {
            curr = curr->next;
        }
    } while (curr != cdll->head);

    return NULL;
}

dll_node_t* cdll_pop(cdll_t* cdll) {
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return NULL;
    }
    if (!cdll->tail) {
        fprintf(stderr, "ERROR: circular doubly linked list is empty.\n");
        return NULL;
    }

    dll_node_t* tail = cdll->tail; // pop tail node

    if (cdll->size == 1) { // if tail is only node, cdll becomes empty
        cdll->head = NULL;
        cdll->tail = NULL;
    } else {
        cdll->tail = cdll->tail->prev;
        cdll->tail->next = cdll->head;
        cdll->head->prev = cdll->tail;
    }

    cdll->size--;
    return tail;
}

dll_node_t* cdll_pop_left(cdll_t* cdll) {
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return NULL;
    }
    if (!cdll->head) {
        fprintf(stderr, "ERROR: circular doubly linked list is empty.\n");
        return NULL;
    }

    dll_node_t* head = cdll->head; // pop head node

    if (cdll->size == 1) { // if head is only node, cdll becomes empty
        cdll->head = NULL;
        cdll->tail = NULL;
    } else {
        cdll->head = cdll->head->next;
        cdll->head->prev = cdll->tail;
        cdll->tail->next = cdll->head;
    }

    cdll->size--;
    return head;
}

size_t cdll_size(const cdll_t* cdll) {
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return (size_t)-1;
    }

    return cdll->size;
}

int cdll_is_empty(const cdll_t* cdll) {
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return -1;
    }

    return (cdll->size == 0);
}

void cdll_print(cdll_t* cdll) { // used for testing
    if (!cdll) {
        fprintf(stderr, "ERROR: circular doubly linked list is NULL.\n");
        return;
    }
    if (cdll->size == 0) {
        printf("EMPTY - Circular Doubly Linked List.\n");
        printf("Circular Doubly Linked List Size = %zu\n", cdll->size);
        return;
    }

    dll_node_t* curr = cdll->head;
    do {
        message_t* curr_msg = (message_t*)curr->data;

        if (cdll->size == 1) {
            printf("HEAD/TAIL: [msg_id: %lld]", curr_msg->id);
        } else if (curr == cdll->head) {
            printf("HEAD: [msg_id: %lld] -> ", curr_msg->id);
        } else if (curr == cdll->tail) {
            printf("[msg_id: %lld]: TAIL", curr_msg->id);
        } else {
            printf("[msg_id: %lld] -> ", curr_msg->id);
        }
        curr = curr->next;
    } while (curr != cdll->head);

    printf("\n");
    printf("Circular Doubly Linked List Size = %zu\n", cdll->size);
    return;
}
