/*
 * ccol/hash_table_iterator.h
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef HASH_TABLE_ITERATOR_H
#define HASH_TABLE_ITERATOR_H

#include "hash_table.h"
#include "iterator.h"

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

#endif // HASH_TABLE_ITERATOR_H
