/*
 * ccol/cdll_internal.c
 *
 * Internal helpers for cdll
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "cdll.h"
#include "cdll_internal.h"
#include "ccol_status.h"
#include "ccol_macros.h"

void cdll_uninit(cdll_t *cdll) {
    if (!cdll || !cdll->is_initialized) return;

    cdll->head = NULL;
    cdll->tail = NULL;
    cdll->size = 0;
    cdll->is_initialized = false;
}
