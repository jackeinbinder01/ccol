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

#include <stddef.h>
#include "dll.h"
#include "hash.h"
#include "iterator.h"
#include "comparator.h"

typedef struct hash_table_t {
    dll_t **buckets;
    int num_buckets;
    size_t size;
    size_t key_size;
    hash_func_t hash_func;
    comparator_t cmp;
} hash_table_t;

// Constructors
void hash_table_init(hash_table_t *hash_table);
hash_table_t *hash_table_create(int num_buckets, size_t key_size, hash_func_t hash_func, comparator_t cmp);

// Insertion
void hash_table_add(hash_table_t *hash_table, void *key, void *data);

// Removal
void hash_table_remove(hash_table_t *hash_table, void *key);

// Access
void *hash_table_get(const hash_table_t *hash_table, void *key);

// Print
void hash_table_print(hash_table_t *hash_table);

// Cleanup
void hash_table_destroy(hash_table_t *hash_table, void (*free_data)(void *));
void hash_table_free(hash_table_t *hash_table);
void hash_table_clear(hash_table_t *hash_table);

// Utilities
void hash_table_swap(hash_table_t *hash_table, void *key1, void *key2);
hash_table_t *hash_table_clone(const hash_table_t *hash_table);
int hash_table_contains(const hash_table_t *hash_table, void *key);
void hash_table_resize(hash_table_t *hash_table, int new_num_buckets);

// Iterator
iterator_t *hash_table_iterator_create(const hash_table_t *hash_table);
iterator_t *hash_table_keys(const hash_table_t *hash_table);
iterator_t *hash_table_values(const hash_table_t *hash_table);

#define HASH_TABLE_FOR(type, var, hash_table_ptr)                                         \
    for (iterator_t *_it = hash_table_iterator_create(hash_table_ptr); _it; _it = NULL)   \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // HASH_TABLE_H
