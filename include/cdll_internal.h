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
ccol_status_t cdll_close_into(const cdll_t *src, cdll_t *dest, copy_func_t copy_data, void *ctx);

#endif // CDLL_INTERNAL_H
