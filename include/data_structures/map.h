/*
 * ccol/map.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "hash_table.h"
#include "iterator.h"
#include "comparator.h"

typedef struct map_t {
    hash_table_t hash_table;
    bool is_initialized;
} map_t;

// Constructors
void map_init(map_t *map);
map_t *map_create(int num_buckets, size_t key_size, hash_policy_t hash_policy, comparator_t cmp);
map_t *map_create_custom(int num_buckets, size_t key_size, hash_func_t hash_func, comparator_t cmp);

// Insertion
void map_put(map_t *map, void *key, void *data);

// Removal
void map_remove(map_t *map, void *key);

// Access
void *map_get(const map_t *map, void *key);
void *map_get_or_default(const map_t *map, void *key, void *default_value);

// Attributes
size_t map_size(const map_t *map);
bool map_is_empty(const map_t *map);
bool map_contains(const map_t *map, void *key);

// Print
void map_print(map_t *map);

// Cleanup
void map_destroy(map_t *map, void (*free_data)(void *));
void map_free(map_t *map);
void map_clear(map_t *map, void (*free_data)(void *));

// Utilities
void map_swap(map_t *map, void *key1, void *key2);
void map_replace(map_t *map, void *key, void *new_value);
map_t *map_clone(const map_t *map);
void map_copy(map_t *dest, const map_t *src);
double map_load_factor(const map_t *map);

// Iterator
iterator_t *map_iterator_create(const map_t *map);
iterator_t *map_keys(const map_t *map);
iterator_t *map_values(const map_t *map);

#define MAP_FOR(type, var, map_ptr)                                                       \
    for (iterator_t *_it = map_iterator_create(map_ptr); _it; _it = NULL)                 \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif //MAP_H
