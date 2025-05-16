/*
 * ccol/ccol.h
 *
 * All public facing ccol APIs.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_H
#define CCOL_H

/* Core */
#include <ccol/ccol_status.h>
#include <ccol/ccol_macros.h>
#include <ccol/ccol_constants.h>

// Container attributes
#include <ccol/ccol_ownership.h>
#include <ccol/ccol_comparator.h>
#include <ccol/ccol_copy.h>
#include <ccol/ccol_free.h>
#include <ccol/ccol_print.h>

// Utilities
#include <ccol/ccol_swap.h>

/* Hash */
#include <ccol/ccol_hash.h>

/* Containers */
#include <ccol/ccol_cdll.h>
#include <ccol/ccol_cdll_iterator.h>

#include <ccol/ccol_dll.h>
#include <ccol/ccol_dll_iterator.h>

#include <ccol/ccol_deque.h>
#include <ccol/ccol_deque_iterator.h>

#include <ccol/ccol_queue.h>
#include <ccol/ccol_queue_iterator.h>

#include <ccol/ccol_stack.h>
#include <ccol/ccol_stack_iterator.h>

#include <ccol/ccol_vector.h>
#include <ccol/ccol_vector_iterator.h>

#include <ccol/ccol_hash_table.h>
#include <ccol/ccol_hash_table_iterator.h>

#endif  // CCOL_H
