/*
 * ccol/ccol_hash_table_iterator.h
 *
 * Iterator for hash table.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_HASH_TABLE_ITERATOR_H
#define CCOL_HASH_TABLE_ITERATOR_H

#include "ccol_hash_table.h"
#include "ccol_iterator.h"

typedef struct ccol_kv_pair {
    void *key;
    void *value;
} ccol_kv_pair_t;

// Iterator
ccol_iterator_t *ccol_hash_table_iterator_create(const ccol_hash_table_t *hash_table);
ccol_iterator_t *ccol_hash_table_keys(const ccol_hash_table_t *hash_table);
ccol_iterator_t *ccol_hash_table_values(const ccol_hash_table_t *hash_table);
ccol_iterator_t *ccol_hash_table_items(const ccol_hash_table_t *hash_table);

#define CCOL_HASH_TABLE_VALUES_FOR(type, var, hash_table_ptr)                                        \
    for (ccol_iterator_t *_it = ccol_hash_table_iterator_create(hash_table_ptr); _it; _it = NULL)    \
        for (type *var = NULL;                                                                       \
            _it->has_next(_it) &&                                                                    \
            ((var = (type *)_it->next(_it)) || 1);)                                                  \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define CCOL_HASH_TABLE_KEYS_FOR(type, var, hash_table_ptr)                                          \
    for (ccol_iterator_t *_it = ccol_hash_table_keys(hash_table_ptr); _it; _it = NULL)               \
        for (type *var = NULL;                                                                       \
            _it->has_next(_it) &&                                                                    \
            ((var = (type *)_it->next(_it)) || 1);)                                                  \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define CCOL_HASH_TABLE_FOR(type, var, hash_table_ptr)                                               \
    CCOL_HASH_TABLE_VALUES_FOR(type, var, hash_table_ptr)

#define CCOL_HASH_TABLE_ITEMS_FOR(kv_pair_var, hash_table_ptr)                                       \
    for (ccol_iterator_t *_it = ccol_hash_table_items(hash_table_ptr); _it; _it = NULL)              \
        for (ccol_kv_pair_t *kv_pair_var = NULL;                                                     \
            _it->has_next(_it) &&                                                                    \
            ((kv_pair_var = (ccol_kv_pair_t *)_it->next(_it)) || 1);)                                \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)



#endif  // CCOL_HASH_TABLE_ITERATOR_H
