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

void cdll_uninit(cdll_t *cdll);
ccol_status_t cdll_clone_into(const cdll_t *src, cdll_t *dest, copy_func_t copy_data, void *ctx);
ccol_status_t cdll_deep_clone_into(const cdll_t *src, cdll_t *dest, void *ctx);
void cdll_clone_rollback(cdll_t *dest, free_func_t free_data, void *ctx);

#endif // CDLL_INTERNAL_H
