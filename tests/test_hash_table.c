/*
* test_hash_table.c / Practicum 1
*
* Jack Einbinder / CS5600 / Northeastern University
* Spring 2025 / March 24, 2025
*
* This file contains unit tests for key functions of the deque data structure.
*
*/

#include "data_structures/dll.h"
#include "data_structures/hash_table.h"
#include "components/message.h"
#include <stdio.h>
#include <stddef.h>

hash_table_t* test_hash_table_init() {
    hash_table_t* hash_table = hash_table_init(16);
    if (!hash_table) {
        fprintf(stderr, "FAIL: test_hash_table_init failed to create hash_table.\n");
        return NULL;
    }
    hash_table_print(hash_table, 'm');
    return hash_table;

}

int test_hash_table_add(hash_table_t* hash_table) {
    if (!hash_table) {
        fprintf(stderr, "FAIL: hash table is NULL.\n");
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

    hash_table_add(hash_table, message_1->id, message_1);
    hash_table_add(hash_table, message_2->id, message_2);
    hash_table_add(hash_table, message_3->id, message_3);
    hash_table_add(hash_table, message_4->id, message_4);
    hash_table_print(hash_table, 'm');
    return 0;
}

int test_hash_table_get(hash_table_t* hash_table) {
    if (!hash_table) {
        fprintf(stderr, "FAIL: hash table is NULL.\n");
        return -1;
    }

    dll_node_t* node_1 = hash_table_get(hash_table, (long long)1);
    if (!node_1) {
        fprintf(stderr, "Failed to get node 1.\n");
        return -1;
    }
    message_print(node_1->data);
    printf("\n");
    dll_node_t* node_2 = hash_table_get(hash_table, (long long)2);
    if (!node_2) {
        fprintf(stderr, "Failed to get node 2.\n");
        return -1;
    }
    message_print(node_2->data);
    printf("\n");
    dll_node_t* node_3 = hash_table_get(hash_table, (long long)3);
    if (!node_3) {
        fprintf(stderr, "Failed to get node 3.\n");
        return -1;
    }
    message_print(node_3->data);
    printf("\n");
    dll_node_t* node_4 = hash_table_get(hash_table, (long long)4);
    if (!node_4) {
        fprintf(stderr, "Failed to get node 4.\n");
        return -1;
    }
    message_print(node_4->data);
    printf("\n");
    return 0;
}

int test_hash_table_remove(hash_table_t* hash_table) {
    if (!hash_table) {
        fprintf(stderr, "FAIL: hash table is NULL.\n");
        return -1;
    }
    hash_table_remove(hash_table, (long long)2);
    hash_table_remove(hash_table, (long long)4);
    hash_table_print(hash_table, 'm');
    return 0;
}

int main(void) {
    // Test hash_table_init
    printf("\nTest: hash_table_init\n\n");
    hash_table_t* hash_table = test_hash_table_init();
    if (!hash_table) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test hash_table_add
    printf("\nTest: hash_table_add\n\n");
    if(test_hash_table_add(hash_table) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }

    // Test hash_table_get
    printf("\nTest: hash_table_get\n\n");
    if(test_hash_table_get(hash_table) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }
    // Test hash_table_remove
    printf("\nTest: hash_table_remove\n\n");
    if(test_hash_table_remove(hash_table) != 0) {
        printf("FAIL\n");
    } else {
        printf("PASS\n");
    }
}