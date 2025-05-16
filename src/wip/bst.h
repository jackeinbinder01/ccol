/*
 * ccol/bst.h
 *
 *
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef BST_H
#define BST_H

#include <stddef.h>
#include <stdbool.h>
#include "vector.h"
#include "iterator.h"
#include "comparator.h"

typedef struct bst_node {
    void *data;
    struct bst_node_t *left;
    struct bst_node_t *right;
} bst_node_t;

typedef struct bst_t {
    bst_node_t *root;
    size_t size;
    comparator_t cmp;

    bool is_initialized;
} bst_t;

// Constructors
void bst_init(bst_t *bst, comparator_t cmp);
bst_t *bst_create(comparator_t cmp);
bst_t *bst_build(vector_t *vec, comparator_t cmp);

// Insertion
void bst_insert(bst_t *bst, void *data);

// Removal
void bst_remove(bst_t *bst, void *data);
void *bst_extract_root(bst_t *bst);

// Access
void *bst_search(const bst_t *bst, const void *data);
void *bst_peek_root(const bst_t *bst);

// Traverse
void bst_inorder_walk(const bst_t *bst, void (*func)(void *));
void bst_preorder_walk(const bst_t *bst, void (*func)(void *));
void bst_postorder_walk(const bst_t *bst, void (*func)(void *));
void bst_bfs_walk(const bst_t *bst, void (*func)(void *));

// Attributes
size_t bst_size(const bst_t *bst);
size_t bst_height(const bst_t *bst);
bool bst_is_empty(const bst_t *bst);
bool bst_is_balanced(const bst_t *bst);
size_t bst_diameter(const bst_t *bst);
bool bst_contains(const bst_t *bst, void *data);
void *bst_min(const bst_t *bst);
void *bst_max(const bst_t *bst);
void *bst_successor(const bst_t *bst, void *data);
void *bst_predecessor(const bst_t *bst, void *data);

// Print
void bst_print(const bst_t *bst);

// Cleanup
void bst_destroy(bst_t *bst, void (*free_data)(void*));
void bst_free(bst_t *bst);
void bst_clear(bst_t *bst, void (*free_data)(void *));

// Utilities
bst_t *bst_clone(const bst_t *bst);
void bst_copy(bst_t *dest, const bst_t *src);
void bst_reverse(bst_t *bst);

// Iterator
iterator_t *bst_iterator_create(const bst_t *bst);
iterator_t *bst_preorder_iterator_create(const bst_t *bst);
iterator_t *bst_inorder_iterator_create(const bst_t *bst);
iterator_t *bst_postorder_iterator_create(const bst_t *bst);
iterator_t *bst_bfs_iterator_create(const bst_t *bst);

#define BST_FOR(type, var, bst_ptr)                                                       \
    for (iterator_t *_it = bst_iterator_create(bst_ptr); _it; _it = NULL)                 \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define BST_FOR_PREORDER(type, var, bst_ptr)                                              \
    for (iterator_t *_it = bst_preorder_iterator_create(bst_ptr); _it; _it = NULL)        \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define BST_FOR_INORDER(type, var, bst_ptr)                                               \
    for (iterator_t *_it = bst_inorder_iterator_create(bst_ptr); _it; _it = NULL)         \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define BST_FOR_POSTORDER(type, var, bst_ptr)                                             \
    for (iterator_t *_it = bst_postorder_iterator_create(bst_ptr); _it; _it = NULL)       \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define BST_FOR_BFS(type, var, bst_ptr)                                                   \
    for (iterator_t *_it = bst_bfs_iterator_create(bst_ptr); _it; _it = NULL)             \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // BST_H
