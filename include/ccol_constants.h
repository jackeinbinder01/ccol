/*
 * ccol/ccol_constants.h
 *
 * Constants
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_CONSTANTS_H
#define CCOL_CONSTANTS_H

// Sentinel value for index not found
#define DLL_INDEX_NOT_FOUND SIZE_MAX
#define CDLL_INDEX_NOT_FOUND SIZE_MAX
#define DEQUE_INDEX_NOT_FOUND SIZE_MAX
#define HASH_TABLE_KEY_NOT_FOUND SIZE_MAX

// Special key_size value: treat key as null-terminated string in hash tables
#define HASH_KEY_STRING 0

// Function types
typedef int (*comparator_func_t)(const void *a, const void *b, void *ctx);
typedef void *(*copy_func_t)(const void *, void *);
typedef void (*free_func_t)(void *, void *);
typedef void (*print_func_t)(const void *, void *);

#endif // CCOL_CONSTANTS_H
