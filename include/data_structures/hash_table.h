/*
 * ccol/hash_table.h
 *
 * Hash table
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "dll.h"
#include <stddef.h>

/*
 * This is the API for a hash table.
 *
 * The hash table is a key component of the cache, enabling quick lookup and retrieval of messages.
 *
 */

typedef struct hash_entry_t {
    long long key;
    dll_node_t* node;
} hash_entry_t;

typedef struct hash_table_t {
    dll_t** buckets;
    int num_buckets;
    size_t size;
} hash_table_t;

hash_table_t* hash_table_init(int num_buckets);
void hash_table_destroy(hash_table_t* hash_table);
int hash_table_add(hash_table_t* hash_table, long long key, void* data);
int hash_table_remove(hash_table_t* hash_table, long long key);
dll_node_t* hash_table_get(hash_table_t* hash_table, long long key);
void hash_table_print(hash_table_t* hash_table, char msg_or_idx);

#endif //HASH_TABLE_H
