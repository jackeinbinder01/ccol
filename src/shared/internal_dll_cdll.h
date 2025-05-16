/*
 * ccol/src/shared/internal_dll_cdll.h
 *
 * Internal helpers for dll (shared with cdll).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_INTERNAL_DLL_CDLL_H
#define CCOL_INTERNAL_DLL_CDLL_H

#include "ccol/ccol_status.h"
#include "ccol/ccol_dll.h"

void ccol__dll_node_free(ccol_dll_node_t *node);
ccol_dll_node_t *ccol__dll_node_get_middle(const ccol_dll_node_t *head, size_t size);
ccol_status_t ccol__dll_node_get_bounded(
    const ccol_dll_node_t *head,
    const ccol_dll_node_t *tail,
    size_t size, size_t index,
    ccol_dll_node_t **node_out
);

#endif  // CCOL_INTERNAL_DLL_CDLL_H
