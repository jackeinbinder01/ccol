/*
* dll.c / Practicum 1
*
* Jack Einbinder / CS5600 / Northeastern University
* Spring 2025 / March 19, 2025
*
*/

#include "../../include/data_structures/dll.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

dll_t* dll_init(void) {
    dll_t* dll = malloc(sizeof(dll_t));
    if (!dll) {
      perror("ERROR: failed to initialize doubly linked list");
      return NULL;
    }

    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;

    return dll;
}

void dll_destroy(dll_t* dll, void (*free_data)(void*)) {
    if (!dll) return;

    dll_node_t* curr = dll->head;
    while (curr) {
      dll_node_t* next = curr->next;

      if (free_data) {
        free_data(curr->data);
      }

      free(curr);
      curr = next;
    }

    free(dll);
    return;
}

int dll_prepend(dll_t* dll, void* data) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
        return -1;
    }

    dll_node_t* new_node = malloc(sizeof(dll_node_t));
    if (!new_node) {
        fprintf(stderr, "ERROR: failed to create new doubly linked node.\n");
        return -1;
    }

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
    return 0;
}

int dll_append(dll_t* dll, void* data) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
        return -1;
    }

    dll_node_t* new_node = malloc(sizeof(dll_node_t));
    if (!new_node) {
        fprintf(stderr, "ERROR: failed to create new doubly linked node.\n");
        return -1;
    }

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
    return 0;
}

int dll_insert_after(dll_t* dll, dll_node_t* target_node, void* data) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
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
    if (!dll->head) {
        dll->head = new_node;
        dll->tail = new_node;
    } else {
        new_node->next = target_node->next;
        new_node->prev = target_node;
        target_node->next = new_node;

        if (new_node->next) {
            new_node->next->prev = new_node;
        } else {
            dll->tail = new_node;
        }
    }
    dll->size++;
    return 0;
}

int dll_insert_before(dll_t* dll, dll_node_t* target_node, void* data) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
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
    new_node->next = target_node;
    new_node->prev = target_node->prev;

    if (target_node->prev) {
        target_node->prev->next = new_node;
    } else { // target_node must be the head
        dll->head = new_node;
    }
    target_node->prev = new_node;

    dll->size++;
    return 0;
}

int dll_delete(dll_t* dll, dll_node_t* target_node) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
        return -1;
    }
    if (!target_node) {
        fprintf(stderr, "ERROR: target node is NULL.\n");
        return -1;
    }

    if (target_node == dll->head) { // delete head node
        dll->head = target_node->next;
        if (target_node->next) {
            target_node->next->prev = NULL;
        }
    } else if (target_node == dll->tail) { // delete tail node
        dll->tail = target_node->prev;
        if (target_node->prev) {
            target_node->prev->next = NULL;
        }
    } else { // delete internal node
      target_node->prev->next = target_node->next;
      target_node->next->prev = target_node->prev;
    }

    free(target_node);
    dll->size--;
    return 0;
}

dll_node_t* dll_search(const dll_t* dll, const void* data, int (*cmp)(const void*, const void*)) { // you wont need this
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
        return NULL;
    }
    if (!cmp) {
        fprintf(stderr, "ERROR: comparator is NULL.\n");
        return NULL;
    }

    dll_node_t* curr = dll->head;
    while (curr) {
        if (cmp(curr->data, data) == 0) {
            return curr;
        } else {
            curr = curr->next;
        }
    }

    return NULL;
}

dll_node_t* dll_pop(dll_t* dll) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
        return NULL;
    }
    if (!dll->tail) {
        fprintf(stderr, "ERROR: doubly linked list is empty.\n");
        return NULL;
    }

    dll_node_t* tail = dll->tail;

    if (dll->tail->prev) {
        dll->tail->prev->next = NULL;
        dll->tail = dll->tail->prev;
    } else {
        dll->head = NULL;
        dll->tail = NULL;
    }

    dll->size--;
    return tail;
}

dll_node_t* dll_pop_left(dll_t* dll) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
        return NULL;
    }
    if (!dll->head) {
        fprintf(stderr, "ERROR: doubly linked list is empty.\n");
        return NULL;
    }

    dll_node_t* head = dll->head;

    if (dll->head->next) { // list contains more than 1 node
        dll->head->next->prev = NULL;
        dll->head = dll->head->next;
    } else {
        dll->head = NULL;
        dll->tail = NULL;
    }

    dll->size--;
    return head;
}

size_t dll_size(const dll_t* dll) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
        return (size_t)-1;
    }

    return dll->size;
}

int dll_is_empty(const dll_t* dll) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
        return -1;
    }

    return (dll->size == 0);
}

void print_dll_node(dll_node_t* node) {
    if (!node) {
        fprintf(stderr, "ERROR: dll node is NULL.\n");
        return;
    }
    message_t* message = (message_t*)node->data;
    if (!message) {
        fprintf(stderr, "ERROR: no message.\n");
        return;
    }

    printf("Message ID: %lld\n", message->id);
    printf("Message Sender: %s\n", message->sender);
    printf("Message Receiver: %s\n", message->receiver);
    printf("Message Content: %s\n", message->content);
    return;
}


void dll_print_idx(dll_t* dll) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
        return;
    }
    if (dll->size == 0) {
        printf("EMPTY - Doubly Linked List.\n");
        printf("Doubly Linked List Size = %zu\n", dll->size);
        return;
    }

    dll_node_t* curr = dll->head;
    while (curr) {
        dll_node_t* next = curr->next;
        int* index_ptr = (int*)curr->data;

        if (dll->size == 1) {
            printf("HEAD/TAIL: [index: %d]", *index_ptr);
        } else if (curr == dll->head) {
            printf("HEAD: [index: %d] -> ", *index_ptr);
        } else if (curr == dll->tail) {
            printf("[index: %d]: TAIL", *index_ptr);
        } else {
            printf("[index: %d] -> ", *index_ptr);
        }
        curr = next;
    }

    printf("\n");
    printf("Doubly Linked List Size = %zu\n", dll->size);
    return;
}

void dll_print(dll_t* dll) {
    if (!dll) {
        fprintf(stderr, "ERROR: doubly linked list is NULL.\n");
        return;
    }
    if (dll->size == 0) {
        printf("EMPTY - Doubly Linked List.\n");
        printf("Doubly Linked List Size = %zu\n", dll->size);
        return;
    }

    dll_node_t* curr = dll->head;
    while (curr) {
        dll_node_t* next = curr->next;
        message_t* curr_msg = (message_t*)curr->data;

        if (dll->size == 1) {
            printf("HEAD/TAIL: [msg_id: %lld]", curr_msg->id);
        } else if (curr == dll->head) {
            printf("HEAD: [msg_id: %lld] -> ", curr_msg->id);
        } else if (curr == dll->tail) {
            printf("[msg_id: %lld]: TAIL", curr_msg->id);
        } else {
            printf("[msg_id: %lld] -> ", curr_msg->id);
        }
        curr = next;
    }

    printf("\n");
    printf("Doubly Linked List Size = %zu\n", dll->size);
    return;
}
