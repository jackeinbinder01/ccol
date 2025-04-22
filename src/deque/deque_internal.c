/*
* ccol/deque_internal.c
 *
 * Internal helpers for deque
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdbool.h>

#include "dll.h"
#include "dll_internal.h"
#include "cdll.h"
#include "cdll_internal.h"
#include "deque.h"
#include "ccol_status.h"

void deque_uninit(deque_t *deque) {
    if (!deque || !deque->is_initialized) return;

    cdll_uninit(&deque->list);
    deque->is_initialized = false;
}

ccol_status_t cdll_close_into(const cdll_t *src, cdll_t *dest, copy_func_t copy_data, void *ctx) {
    cdll_t *cdll;
    ccol_status_t status = cdll_clone(src, &dest, copy_data, ctx);

    if (status != CCOL_STATUS_OK) return status;


}