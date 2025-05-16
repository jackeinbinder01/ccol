/*
 * ccol/src/cdll/internal.h
 *
 * Internal helper functions for circular doubly-linked list (cdll).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_CDLL_INTERNAL_H
#define CCOL_CDLL_INTERNAL_H

#include "ccol/ccol_cdll.h"
#include "ccol/ccol_dll.h"

ccol_status_t ccol__cdll_uninit(ccol_cdll_t *cdll);
ccol_status_t ccol__cdll_clone_into(const ccol_cdll_t *src, ccol_cdll_t *dest);
ccol_status_t ccol__cdll_deep_clone_into(const ccol_cdll_t *src, ccol_cdll_t *dest);
ccol_status_t ccol__cdll_clone_rollback(ccol_cdll_t *dest);
void ccol__cdll_dispose_node(ccol_cdll_t *cdll, ccol_dll_node_t *node);
ccol_dll_node_t *ccol__cdll_search_bounded(
    const ccol_cdll_t *cdll,
    const ccol_dll_node_t *head,
    size_t size,
    const void *data
);

#endif  // CCOL_CDLL_INTERNAL_H
