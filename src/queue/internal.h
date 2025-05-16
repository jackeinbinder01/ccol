/*
 * ccol/src/queue/internal.h
 *
 * Internal helper functions for queue (FIFO).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_QUEUE_INTERNAL_H
#define CCOL_QUEUE_INTERNAL_H

#include "ccol/ccol_queue.h"

ccol_status_t queue__uninit(ccol_queue_t *vec);

#endif  // CCOL_QUEUE_INTERNAL_H
