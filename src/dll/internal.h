/*
 * ccol/src/dll/internal.h
 *
 * Internal helpers for dll (shared with cdll)
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_DLL_INTERNAL_H
#define CCOL_DLL_INTERNAL_H

#include "ccol_dll.h"

// dll & cdll
ccol_dll_node_t *ccol__dll_get_middle_node(const ccol_dll_node_t *head, size_t size);
void ccol__dll_free_node(ccol_dll_node_t *node);
void ccol__dll_dispose_node(ccol_dll_t *dll, ccol_dll_node_t *node);

ccol_dll_node_t *ccol__dll_search_bounded(
    const ccol_dll_t *dll,
    const ccol_dll_node_t *head,
    size_t size,
    const void *data
);
ccol_status_t ccol__dll_get_node_bounded(
    const ccol_dll_node_t *head,
    const ccol_dll_node_t *tail,
    size_t size,
    size_t index,
    ccol_dll_node_t **node_out
);

// dll specific
ccol_status_t ccol__dll_uninit(ccol_dll_t *dll);
ccol_status_t ccol__dll_clone_into(const ccol_dll_t *src, ccol_dll_t *dest);
ccol_status_t ccol__dll_deep_clone_into(const ccol_dll_t *src, ccol_dll_t *dest);
ccol_status_t ccol__dll_clone_rollback(ccol_dll_t *dest);

#endif  // CCOL_DLL_INTERNAL_H
