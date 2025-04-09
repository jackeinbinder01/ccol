/*
 * ccol/hash_table_internal.c
 *
 * Hash table internal functions
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdint.h>
#include "hash_table_internal.h"
#include "hash.h"
#include "ccol_constants.h"

#include <stdio.h>

void hash_table_resize_if_needed(hash_table_t *hash_table);

hash_func_t infer_hash_func(size_t key_size) {
    if (key_size == HASH_KEY_STRING) return hash_str;

    switch(key_size) {
        case sizeof(int8_t):     return hash_int8;
        case sizeof(int16_t):    return hash_int16;
        case sizeof(int32_t):    return hash_int32;
        case sizeof(int64_t):    return hash_int64;
        default:
            fprintf(stderr, "infer_hash_func: unsupported key size: %zu\n", key_size);
        return NULL;
    }
}
