/*
 * ccol/avl.h
 *
 * AVL tree (self-balancing binary search tree)
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef AVL_H
#define AVL_H

#include <stddef.h>
#include <stdbool.h>
#include "vector.h"
#include "iterator.h"
#include "comparator.h"

typedef struct ccol_avl_node {
    void *data;
    struct avl_node_t *left;
    struct avl_node_t *right;

    int height;
} ccol_avl_node_t;

typedef struct ccol_avl {
    ccol_avl_node_t *root;
    size_t size;
    comparator_t cmp;

    bool is_initialized;
} ccol_avl_t;

// Constructors
void avl_init(ccol_avl_t *avl, comparator_t cmp);
ccol_avl_t *avl_create(comparator_t cmp);
ccol_avl_t *avl_build(vector_t *vec, comparator_t cmp);

// Insertion
void avl_insert(ccol_avl_t *avl, void *data);

// Removal
void avl_remove(ccol_avl_t *avl, void *data);
void *avl_extract_root(ccol_avl_t *avl);

// Access
void *avl_search(const ccol_avl_t *avl, const void *data);
void *avl_peek_root(const ccol_avl_t *avl);

// Traverse
void avl_inorder_walk(const ccol_avl_t *avl, void (*func)(void *));
void avl_preorder_walk(const ccol_avl_t *avl, void (*func)(void *));
void avl_postorder_walk(const ccol_avl_t *avl, void (*func)(void *));
void avl_bfs_walk(const ccol_avl_t *avl, void (*func)(void *));

// Attributes
size_t avl_size(const ccol_avl_t *avl);
size_t avl_height(const ccol_avl_t *avl);
bool avl_is_empty(const ccol_avl_t *avl);
bool avl_is_balanced(const ccol_avl_t *avl);
size_t avl_diameter(const ccol_avl_t *avl);
bool avl_contains(const ccol_avl_t *avl, void *data);
void *avl_min(const ccol_avl_t *avl);
void *avl_max(const ccol_avl_t *avl);
void *avl_successor(const ccol_avl_t *avl, void *data);
void *avl_predecessor(const ccol_avl_t *avl, void *data);

// Print
void avl_print(const ccol_avl_t *avl);

// Cleanup
void avl_destroy(ccol_avl_t *avl, void (*free_data)(void*));
void avl_free(ccol_avl_t *avl);
void avl_clear(ccol_avl_t *avl, void (*free_data)(void *));

// Utilities
ccol_avl_t *avl_clone(const ccol_avl_t *avl);
void avl_copy(ccol_avl_t *dest, const ccol_avl_t *src);
void avl_reverse(ccol_avl_t *avl);

// Iterator
iterator_t *avl_iterator_create(const ccol_avl_t *avl);
iterator_t *avl_preorder_iterator_create(const ccol_avl_t *avl);
iterator_t *avl_inorder_iterator_create(const ccol_avl_t *avl);
iterator_t *avl_postorder_iterator_create(const ccol_avl_t *avl);
iterator_t *avl_bfs_iterator_create(const ccol_avl_t *avl);

#define AVL_FOR(type, var, avl_ptr)                                                       \
    for (iterator_t *_it = avl_iterator_create(avl_ptr); _it; _it = NULL)                 \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define AVL_FOR_PREORDER(type, var, avl_ptr)                                              \
    for (iterator_t *_it = avl_preorder_iterator_create(avl_ptr); _it; _it = NULL)        \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define AVL_FOR_INORDER(type, var, avl_ptr)                                               \
    for (iterator_t *_it = avl_inorder_iterator_create(avl_ptr); _it; _it = NULL)         \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define AVL_FOR_POSTORDER(type, var, avl_ptr)                                             \
    for (iterator_t *_it = avl_postorder_iterator_create(avl_ptr); _it; _it = NULL)       \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define AVL_FOR_BFS(type, var, avl_ptr)                                                   \
    for (iterator_t *_it = avl_bfs_iterator_create(avl_ptr); _it; _it = NULL)             \
        for (type *var = NULL;                                                            \
            _it->has_next(_it) &&                                                         \
            ((var = (type *)_it->next(_it)) || 1);)                                       \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // AVL_H
