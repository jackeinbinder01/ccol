/*
 * ccol/ccol_constants.h
 *
 * Useful constants.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_CONSTANTS_H
#define CCOL_CONSTANTS_H

#include <stddef.h>

// Sentinel values
#define CCOL_DLL_INDEX_NOT_FOUND SIZE_MAX
#define CCOL_CDLL_INDEX_NOT_FOUND SIZE_MAX
#define CCOL_DEQUE_INDEX_NOT_FOUND SIZE_MAX
#define CCOL_HASH_TABLE_KEY_NOT_FOUND SIZE_MAX

// Special key_size value: treat key as null-terminated string in hash tables
#define CCOL_HASH_KEY_STRING 0

// Core function pointer types
typedef void *(*ccol_copy_func_t)(const void *, void *);
typedef void (*ccol_free_func_t)(void *, void *);
typedef void (*ccol_print_func_t)(const void *, void *);

#endif  // CCOL_CONSTANTS_H
