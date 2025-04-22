/*
 * ccol/dll_internal.h
 *
 * Internal helpers for dll (shared with cdll)
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef DLL_INTERNAL_H
#define DLL_INTERNAL_H

#include "dll.h"

// DLL & CDLL
dll_node_t *dll_get_middle_node(const dll_node_t *head, size_t size);
void dll_free_node(dll_node_t *node);
void dll_dispose_node(dll_node_t *node, void (*free_data)(void *, void *), void *ctx);

dll_node_t *dll_search_bounded(const dll_node_t *head, size_t size, const void *data, int (*cmp)(const void *, const void *, void *), void *ctx);

ccol_status_t dll_get_node_bounded(const dll_node_t *head, const dll_node_t *tail, size_t size, size_t index, dll_node_t **node_out);

// DLL specific
void dll_uninit(dll_t *dll);

#endif // DLL_INTERNAL_H
