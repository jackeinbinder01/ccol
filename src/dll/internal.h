/*
 * ccol/src/dll/internal.h
 *
 * Internal helpers for dll (shared with cdll).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_DLL_INTERNAL_H
#define CCOL_DLL_INTERNAL_H

#include "ccol/ccol_dll.h"

void ccol__dll_dispose_node(ccol_dll_t *dll, ccol_dll_node_t *node);
ccol_dll_node_t *ccol__dll_search_bounded(
    const ccol_dll_t *dll,
    const ccol_dll_node_t *head,
    size_t size,
    const void *data
);
ccol_status_t ccol__dll_uninit(ccol_dll_t *dll);
ccol_status_t ccol__dll_clone_into(const ccol_dll_t *src, ccol_dll_t *dest);
ccol_status_t ccol__dll_deep_clone_into(const ccol_dll_t *src, ccol_dll_t *dest);
ccol_status_t ccol__dll_clone_rollback(ccol_dll_t *dest);

#endif  // CCOL_DLL_INTERNAL_H
