/*
* test_cdll.c / Practicum 1
*
* Jack Einbinder / CS5600 / Northeastern University
* Spring 2025 / March 19, 2025
*
* This file contains unit tests for key functions of the cdll data structure.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "data_structures/dll.h"
#include "data_structures/cdll.h"
#include "components/message.h"

cdll_t* test_cdll_init() {
    cdll_t* cdll = cdll_init();
    if (!cdll) {
        fprintf(stderr, "FAIL: test_cdll_init failed to create cdll.\n");
        return NULL;
    }
    cdll_print(cdll);
    return cdll;
}

int test_cdll_append(cdll_t* cdll) {
    if (!cdll) {
        fprintf(stderr, "ERROR: cdll is NULL.\n");
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

    cdll_append(cdll, message_1);
    cdll_append(cdll, message_2);
    cdll_append(cdll, message_3);
    cdll_append(cdll, message_4);
    cdll_print(cdll);

    return 0;
}

int test_cdll_pop_left(cdll_t* cdll) {
    if (!cdll) {
        fprintf(stderr, "ERROR: cdll is NULL.\n");
        return -1;
    }

    dll_node_t* head = cdll_pop_left(cdll);
    free(head);
    cdll_print(cdll);
    return 0;
}

int test_cdll_delete(cdll_t* cdll) {
    if (!cdll) {
        fprintf(stderr, "ERROR: cdll is NULL.\n");
        return -1;
    }

    message_t search_id = { .id = 3 };
    dll_node_t* node_id_3 = cdll_search(cdll, &search_id, message_cmp_id);
    if (!node_id_3) {
        fprintf(stderr, "ERROR: failed to search for node.\n");
        return -1;
    }
    cdll_delete(cdll, node_id_3);
    cdll_print(cdll);
    return 0;
}

int main(void) {

    // Test cdll_init
    printf("\nTest: cdll_init\n\n");
    cdll_t* cdll = test_cdll_init();
    if (!cdll) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test cdll_append
    printf("\nTest: cdll_append\n\n");
    if(test_cdll_append(cdll) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test cdll_pop_left
    printf("\nTest: cdll_pop_left\n\n");
    if(test_cdll_pop_left(cdll) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test cdll_delete
    printf("\nTest: cdll_delete\n\n");
    if(test_cdll_delete(cdll) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    return 0;
}