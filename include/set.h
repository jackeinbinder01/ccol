/*
 * ccol/set.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include "hash_table.h"
#include "iterator.h"
#include "comparator.h"

typedef struct set_t {
    hash_table_t hash_table;
    bool is_initialized;
} set_t;

// Constructors
void set_init(set_t *set);
set_t *set_create(int num_buckets, size_t key_size, hash_policy_t hash_policy, comparator_t cmp);
set_t *set_create_custom(int num_buckets, size_t key_size, hash_func_t hash_func, comparator_t cmp);

// Insertion
void set_add(set_t *set, void *key);

// Removal
void set_remove(set_t *set, void *key);

// Access
void *set_get(const set_t *set, void *key);

// Attributes
size_t set_size(const set_t *set);
bool set_is_empty(const set_t *set);
bool set_contains(const set_t *set, void *key);

// Utilities
void set_swap(set_t *set, void *key1, void *key2);
set_t *set_clone(const set_t *set);
void set_copy(set_t *dest, const set_t *src);
double set_load_factor(const set_t *set);

// Print
void set_print(set_t *set);

// Cleanup
void set_destroy(set_t *set, void (*free_data)(void *));
void set_free(set_t *set);
void set_clear(set_t *set, void (*free_data)(void *));

// Iterator
iterator_t *set_iterator_create(const set_t *set);

#define SET_FOR(type, var, set_ptr)                                               \
    for (iterator_t *_it = set_iterator_create(set_ptr); _it; _it = NULL)         \
        for (type *var = NULL;                                                    \
            _it->has_next(_it) &&                                                 \
            ((var = (type *)_it->next(_it)) || 1);)                               \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif //SET_H
