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
void dll_dispose_node(dll_t *dll, dll_node_t *node);

dll_node_t *dll_search_bounded(const dll_t *dll, const dll_node_t *head, size_t size, const void *data);

ccol_status_t dll_get_node_bounded(const dll_node_t *head, const dll_node_t *tail, size_t size, size_t index, dll_node_t **node_out);

// DLL specific
ccol_status_t dll_uninit(dll_t *dll);
ccol_status_t dll_clone_into(const dll_t *src, dll_t *dest);
ccol_status_t dll_deep_clone_into(const dll_t *src, dll_t *dest);
ccol_status_t dll_clone_rollback(dll_t *dest);

#endif // DLL_INTERNAL_H
