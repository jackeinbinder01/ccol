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
#include "ccol_macros.h"

void deque_uninit(deque_t *deque) {
    if (!deque || !deque->is_initialized) return;

    cdll_uninit(&deque->list);
    deque->is_initialized = false;
}