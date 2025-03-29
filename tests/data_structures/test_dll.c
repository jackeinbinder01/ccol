/*
* test_dll.c / Practicum 1
*
* Jack Einbinder / CS5600 / Northeastern University
* Spring 2025 / March 24, 2025
*
* This file contains unit tests for key functions of the dll data structure.
*
*/

#include <stdio.h>
#include <stddef.h>
#include "data_structures/dll.h"

dll_t* test_dll_init() {
    dll_t* dll = dll_init();
    if (!dll) {
        fprintf(stderr, "FAIL: test_dll_init failed to create dll.\n");
        return NULL;
    }
    dll_print(dll);
    return dll;
}

int test_dll_append(dll_t* dll) {
    if (!dll) {
        fprintf(stderr, "ERROR: dll is NULL.\n");
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
    if (!message_4) {
        fprintf(stderr, "Failed to create message 4.\n");
        return -1;
    }

    dll_append(dll, message_1);
    dll_append(dll, message_2);
    dll_append(dll, message_3);
    dll_append(dll, message_4);
    dll_print(dll);

    return 0;
}

int test_dll_pop_left(dll_t* dll) {
    if (!dll) {
        fprintf(stderr, "ERROR: dll is NULL.\n");
        return -1;
    }

    dll_node_t* head = dll_pop_left(dll);
    free(head);
    dll_print(dll);
    return 0;
}

int test_dll_delete(dll_t* dll) {
    if (!dll) {
        fprintf(stderr, "ERROR: dll is NULL.\n");
        return -1;
    }

    message_t search_id = { .id = 3 };
    dll_node_t* node_id_3 = dll_search(dll, &search_id, message_cmp_id);
    if (!node_id_3) {
        fprintf(stderr, "ERROR: failed to search for node.\n");
        return -1;
    }
    dll_delete(dll, node_id_3);
    dll_print(dll);
    return 0;
}

int main(void) {

    // Test dll_init
    printf("\nTest: dll_init\n\n");
    dll_t* dll = test_dll_init();
    if (!dll) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test dll_append
    printf("\nTest: dll_append\n\n");
    if(test_dll_append(dll) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test dll_pop_left
    printf("\nTest: dll_pop_left\n\n");
    if(test_dll_pop_left(dll) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test dll_delete
    printf("\nTest: dll_delete\n\n");
    if(test_dll_delete(dll) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    return 0;
}