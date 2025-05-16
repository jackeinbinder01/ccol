/*
 * ccol/hash_table_iterator.c
 *
 * Hash table iterator
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "hash_table.h"
#include "iterator.h"

// Iterator
iterator_t *hash_table_iterator_create(const hash_table_t *hash_table);
iterator_t *hash_table_keys(const hash_table_t *hash_table);
iterator_t *hash_table_values(const hash_table_t *hash_table);

