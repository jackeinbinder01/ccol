/*
* test_deque.c / Practicum 1
*
* Jack Einbinder / CS5600 / Northeastern University
* Spring 2025 / March 19, 2025
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "data_structures/cdll.h"
#include "data_structures/deque.h"
#include "components/message.h"

/*
typedef struct deque_t {
    cdll_t* list;
} deque_t;
*/

/* Operation Prototypes */
deque_t* deque_init();
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

deque_t* test_deque_init() {
    deque_t* deque = deque_init();
    if (!deque) {
        fprintf(stderr, "FAIL: test_deque_init failed to create deque.\n");
        return NULL;
    }
    deque_print(deque);
    return deque;
}

int test_deque_push(deque_t* deque) {
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return -1;
    }
    message_t* message_1 = create_msg("shrute_farms", "world", "Hello world.");
    if (!message_1) {
        fprintf(stderr, "Failed to create message 1.\n");
        return -1;
    }
    message_t* message_2 = create_msg("michael_scott", "charles_miner", "Miner? I hardly know her.");
    if (!message_2) {
        fprintf(stderr, "Failed to create message 2.\n");
        return -1;
    }
    message_t* message_3 = create_msg("julius_ceaser", "brutus", "Et tu, Brute?");
    if (!message_3) {
        fprintf(stderr, "Failed to create message 3.\n");
        return -1;
    }
    message_t* message_4 = create_msg("george", "jerry", "I'm out!");
    if (!message_3) {
        fprintf(stderr, "Failed to create message 3.\n");
        return -1;
    }

    deque_push(deque, message_1);
    deque_push(deque, message_2);
    deque_push(deque, message_3);
    deque_push(deque, message_4);
    deque_print(deque);

    return 0;
}

int test_deque_pop_left(deque_t* deque) {
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return -1;
    }

    dll_node_t* head = deque_pop_left(deque);
    free(head);
    deque_print(deque);
    return 0;
}

int test_deque_delete(deque_t* deque) {
    if (!deque) {
        fprintf(stderr, "ERROR: deque is NULL.\n");
        return -1;
    }

    message_t search_id = { .id = 3 };
    dll_node_t* node_id_3 = deque_search(deque, &search_id, message_cmp_id);
    if (!node_id_3) {
        fprintf(stderr, "ERROR: failed to search for node.\n");
        return -1;
    }
    deque_delete(deque, node_id_3);
    deque_print(deque);
    return 0;
}

int main(void) {

    // Test deque_init
    printf("\nTest: deque_init\n\n");
    deque_t* deque = test_deque_init();
    if (!deque) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test deque_push
    printf("\nTest: deque_push\n\n");
    if(test_deque_push(deque) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test deque_pop_left
    printf("\nTest: deque_pop_left\n\n");
    if(test_deque_pop_left(deque) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test deque_delete
    printf("\nTest: deque_delete\n\n");
    if(test_deque_delete(deque) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    return 0;
}