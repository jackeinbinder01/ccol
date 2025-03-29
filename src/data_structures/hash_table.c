/*
* hash_table.c / Practicum 1
*
* Jack Einbinder / CS5600 / Northeastern University
* Spring 2025 / March 19, 2025
*
*/

#include "../../include/data_structures/hash_table.h"
#include "../../include/components/message.h"
#include <stdlib.h>
#include <stdio.h>

static int hash_function(long long key, int num_buckets) {
    return key % num_buckets;
}

void free_hash_entry(void *data) {
    hash_entry_t* hash_entry = (hash_entry_t*)data;
    if (!hash_entry) return;

    if (hash_entry->node) {
        free(hash_entry->node->data);
        free(hash_entry->node);
    }

    free(hash_entry);
}

hash_table_t* hash_table_init(int num_buckets) {
    if (num_buckets <= 0) {
        fprintf(stderr,"ERROR: invalid number of buckets '%d'.\n", num_buckets);
        return NULL;
    }

    // malloc for hash table
    hash_table_t* hash_table = malloc(sizeof(hash_table_t));
    if (!hash_table) {
        perror("ERROR: failed to allocate memory for hash table");
        return NULL;
    }

    // malloc for hash tables' array of linked lists
    hash_table->buckets = malloc(num_buckets * sizeof(dll_t*));
    if (!hash_table->buckets) {
        perror("ERROR: failed to allocate memory for hash table buckets");
        free(hash_table);
        return NULL;
    }

    // init a dll for each bucket
    for (int i = 0; i < num_buckets; i++) {
        hash_table->buckets[i] = dll_init();

        // free hash table and buckets if malloc fails
        if (!hash_table->buckets[i]) {
            fprintf(stderr, "ERROR: failed to initialize bucket number '%d'.\n", i);
            for (int j = 0; j < i; j++) {
                dll_destroy(hash_table->buckets[j], free_hash_entry);
            }
            free(hash_table->buckets);
            free(hash_table);
            return NULL;
        }
    }

    hash_table->num_buckets = num_buckets;
    hash_table->size = 0;

    return hash_table;
}

void hash_table_destroy(hash_table_t* hash_table) {
    if (!hash_table) return;

    for (int i = 0; i < hash_table->num_buckets; i++) {
        dll_destroy(hash_table->buckets[i], free_hash_entry);
    }

    free(hash_table->buckets);
    free(hash_table);
    return;
}

int hash_table_add(hash_table_t* hash_table, long long key, void* data) {
    if (!hash_table) {
        fprintf(stderr, "ERROR: hash_table is NULL.\n");
        return -1;
    }

    int hash_key = hash_function(key, hash_table->num_buckets);
    if (dll_prepend(hash_table->buckets[hash_key], data) != 0) {
        fprintf(stderr, "ERROR: failed to prepend data to buckets[%d] with key '%lld'.", hash_key, key);
        return -1;
    }

    hash_table->size++;
    return 0;
}

int hash_table_remove(hash_table_t* hash_table, long long key) {
    if (!hash_table) {
        fprintf(stderr, "ERROR: hash_table is NULL.\n");
        return -1;
    }

    int hash_key = hash_function(key, hash_table->num_buckets);
    dll_t* bucket = hash_table->buckets[hash_key];
    dll_node_t* target_node = dll_search(bucket, (void*)&key, message_cmp_id);
    if (!target_node) {
        fprintf(stderr, "ERROR: key '%lld' not found in bucket[%d].\n", key, hash_key);
        return -1;
    }

    if (dll_delete(bucket, target_node) != 0) {
        fprintf(stderr, "ERROR: failed to delete target node.\n");
        return -1;
    }

    hash_table->size--;
    return 0;
}

dll_node_t* hash_table_get(hash_table_t* hash_table, long long key) {
    if (!hash_table) {
        fprintf(stderr, "ERROR: hash_table is NULL.\n");
        return NULL;
    }

    int hash_key = hash_function(key, hash_table->num_buckets);
    dll_t* bucket = hash_table->buckets[hash_key];
    dll_node_t* target_node = dll_search(bucket, (void*)&key, message_cmp_id);
    if (!target_node) {
        return NULL;
    }

    return target_node;
}

void hash_table_print(hash_table_t* hash_table, char msg_or_idx) {
    void (*dll_print_func)(dll_t*);
    dll_print_func = NULL;
    switch (msg_or_idx) {
        case 'm':
          dll_print_func = dll_print;
          break;
        case 'i':
          dll_print_func = dll_print_idx;
          break;
        default:
          fprintf(stderr, "ERROR: invalid msg_or_idx\n");
          return;
    }

    if (!hash_table) {
        fprintf(stderr, "ERROR: hash_table is NULL.\n");
        return;
    }

    if (hash_table->size == 0) {
        printf("EMPTY - Hash Table\n");
        printf("\n");
        printf("Number of Buckets =  %d.\n", hash_table->num_buckets);
        printf("Hash Table Size = %zu.\n", hash_table->size);
        return;
    }

    for (int i = 0; i < hash_table->num_buckets; i++) {
        printf("Bucket[%d]: ", i);
        dll_print_func(hash_table->buckets[i]);
    }

    printf("\n");
    printf("Number of Buckets = %d.\n", hash_table->num_buckets);
    printf("Hash Table Size = %zu.\n", hash_table->size);
}
