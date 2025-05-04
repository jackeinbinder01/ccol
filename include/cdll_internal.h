/*
 * ccol/cdll_internal.h
 *
 * Internal helpers for cdll
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CDLL_INTERNAL_H
#define CDLL_INTERNAL_H

#include "dll.h"
#include "dll_internal.h"
#include "cdll.h"

ccol_status_t cdll_uninit(cdll_t *cdll);
ccol_status_t cdll_clone_into(const cdll_t *src, cdll_t *dest);
ccol_status_t cdll_deep_clone_into(const cdll_t *src, cdll_t *dest);
ccol_status_t cdll_clone_rollback(cdll_t *dest);
void cdll_dispose_node(dll_t *cdll, dll_node_t *node);

#endif // CDLL_INTERNAL_H
