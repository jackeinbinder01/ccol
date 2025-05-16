/*
 * ccol/src/iterator/ccol_hash_table_iterator.c
 *
 * Iterator implementation for hash table.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "ccol/ccol_hash_table.h"
#include "ccol/ccol_iterator.h"

// Iterator
ccol_iterator_t *ccol_hash_table_iterator_create(const ccol_hash_table_t *hash_table);
ccol_iterator_t *ccol_hash_table_keys(const ccol_hash_table_t *hash_table);
ccol_iterator_t *ccol_hash_table_values(const ccol_hash_table_t *hash_table);
ccol_iterator_t *ccol_hash_table_items(const ccol_hash_table_t *hash_table);

