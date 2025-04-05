/*
 * ccol/rb_tree.h
 *
 * Red/black tree (self-balancing, non-strictly balanced binary search tree)
 *
 * Created by jackeinbinder
 * Copyright (C) 2025 jackeinbinder
 */

#ifndef RB_TREE_H
#define RB_TREE_H

#include <stddef.h>
#include <stdbool.h>
#include "vector.h"
#include "iterator.h"
#include "comparator.h"

typedef enum {
    COLOR_RED,
    COLOR_BLACK,
} color_t;

typedef struct rb_tree_node_t {
    void *data;

    struct rb_tree_node_t *left;
    struct rb_tree_node_t *right;
    struct rb_tree_node_t *parent;

    color_t color;

    bool is_initialized;
} rb_tree_node_t;

typedef struct rb_tree_t {
    rb_tree_node_t *root;
    size_t size;
    comparator_t cmp;
} rb_tree_t;

// Constructors
void rb_tree_init(rb_tree_t *rb_tree, comparator_t cmp);
rb_tree_t *rb_tree_create(comparator_t cmp);
rb_tree_t *rb_tree_build(vector_t *vec, comparator_t cmp);

// Insertion
void rb_tree_insert(rb_tree_t *rb_tree, void *data);

// Removal
void rb_tree_remove(rb_tree_t *rb_tree, void *data);
void *rb_tree_extract_root(rb_tree_t *rb_tree);

// Access
void *rb_tree_search(const rb_tree_t *rb_tree, const void *data);
void *rb_tree_peek_root(const rb_tree_t *rb_tree);

// Traverse
void rb_tree_inorder_walk(const rb_tree_t *rb_tree, void (*func)(void *));
void rb_tree_preorder_walk(const rb_tree_t *rb_tree, void (*func)(void *));
void rb_tree_postorder_walk(const rb_tree_t *rb_tree, void (*func)(void *));
void rb_tree_bfs_walk(const rb_tree_t *rb_tree, void (*func)(void *));

// Attributes
size_t rb_tree_size(const rb_tree_t *rb_tree);
size_t rb_tree_height(const rb_tree_t *rb_tree);
bool rb_tree_is_empty(const rb_tree_t *rb_tree);
bool rb_tree_is_balanced(const rb_tree_t *rb_tree);
size_t rb_tree_diameter(const rb_tree_t *rb_tree);
bool rb_tree_contains(const rb_tree_t *rb_tree, void *data);
void *rb_tree_min(const rb_tree_t *rb_tree);
void *rb_tree_max(const rb_tree_t *rb_tree);
void *rb_tree_successor(const rb_tree_t *rb_tree, void *data);
void *rb_tree_predecessor(const rb_tree_t *rb_tree, void *data);

// Print
void rb_tree_print(const rb_tree_t *rb_tree);

// Cleanup
void rb_tree_destroy(rb_tree_t *rb_tree, void (*free_data)(void*));
void rb_tree_free(rb_tree_t *rb_tree);
void rb_tree_clear(rb_tree_t *rb_tree, void (*free_data)(void *));

// Utilities
rb_tree_t *rb_tree_clone(const rb_tree_t *rb_tree);
void rb_tree_copy(rb_tree_t *dest, const rb_tree_t *src);
void rb_tree_reverse(rb_tree_t *rb_tree);

// Iterator
iterator_t *rb_tree_iterator_create(const rb_tree_t *rb_tree);
iterator_t *rb_tree_preorder_iterator_create(const rb_tree_t *rb_tree);
iterator_t *rb_tree_inorder_iterator_create(const rb_tree_t *rb_tree);
iterator_t *rb_tree_postorder_iterator_create(const rb_tree_t *rb_tree);
iterator_t *rb_tree_bfs_iterator_create(const rb_tree_t *rb_tree);

#define RB_TREE_FOR(type, var, rb_tree_ptr)                                                   \
    for (iterator_t *_it = rb_tree_iterator_create(rb_tree_ptr); _it; _it = NULL)             \
        for (type *var = NULL;                                                                \
            _it->has_next(_it) &&                                                             \
            ((var = (type *)_it->next(_it)) || 1);)                                           \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define RB_TREE_FOR_PREORDER(type, var, rb_tree_ptr)                                          \
    for (iterator_t *_it = rb_tree_preorder_iterator_create(rb_tree_ptr); _it; _it = NULL)    \
        for (type *var = NULL;                                                                \
            _it->has_next(_it) &&                                                             \
            ((var = (type *)_it->next(_it)) || 1);)                                           \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define RB_TREE_FOR_INORDER(type, var, rb_tree_ptr)                                           \
    for (iterator_t *_it = rb_tree_inorder_iterator_create(rb_tree_ptr); _it; _it = NULL)     \
        for (type *var = NULL;                                                                \
            _it->has_next(_it) &&                                                             \
            ((var = (type *)_it->next(_it)) || 1);)                                           \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define RB_TREE_FOR_POSTORDER(type, var, rb_tree_ptr)                                         \
    for (iterator_t *_it = rb_tree_postorder_iterator_create(rb_tree_ptr); _it; _it = NULL)   \
        for (type *var = NULL;                                                                \
            _it->has_next(_it) &&                                                             \
            ((var = (type *)_it->next(_it)) || 1);)                                           \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#define RB_TREE_FOR_BFS(type, var, rb_tree_ptr)                                               \
    for (iterator_t *_it = rb_tree_bfs_iterator_create(rb_tree_ptr); _it; _it = NULL)         \
        for (type *var = NULL;                                                                \
            _it->has_next(_it) &&                                                             \
            ((var = (type *)_it->next(_it)) || 1);)                                           \
            for (int _done = (_it->destroy(_it), 0); !_done; _done = 1)

#endif // RB_TREE_H
