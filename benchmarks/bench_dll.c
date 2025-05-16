/*
 * ccol/benchmarks/bench_dll.c
 *
 * Doubly-linked list (dll) benchmark.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ccol/ccol_dll.h"
#include "ccol/ccol_status.h"

#include "timer.h"
#include "bench_utils.h"

#define ELEMENT_COUNT 1000000 // 1M

static ccol_status_t bench_ccol_dll_push_back(size_t n) {
    ccol_dll_t list;
    ccol_status_t status = ccol_dll_init(
        &list,
        (ccol_copy_t){0},
        (ccol_free_t){0},
        (ccol_print_t){0},
        (ccol_comparator_t){0}
    );
    if (status != CCOL_STATUS_OK) {
        fprintf(stderr, "ccol_dll_init failed: %s", ccol_strstatus(status));
        return status;
    }

    int data = rand();
    timer_t timer;

    start_timer(&timer);
    for (size_t i = 0; i < n; i++) ccol_dll_push_back(&list, &data);

    double elapsed = stop_timer(&timer, TIME_SCALE_MILLISECONDS);
    PRINT_BENCH("ccol_dll_push_back", n, elapsed, TIME_SCALE_MILLISECONDS);

    ccol_dll_destroy(&list);

    return CCOL_STATUS_OK;
}

//TODO
static ccol_status_t bench_ccol_dll_push_front(size_t n) {
    return CCOL_STATUS_NOT_IMPLEMENTED;
}

//TODO
static ccol_status_t bench_ccol_dll_get(size_t n) {
    return CCOL_STATUS_NOT_IMPLEMENTED;
}

//TODO
static ccol_status_t bench_ccol_dll_contains(size_t n) {
    return CCOL_STATUS_NOT_IMPLEMENTED;
}

//TODO
static ccol_status_t bench_ccol_dll_pop_back(size_t n) {
    return CCOL_STATUS_NOT_IMPLEMENTED;
}

//TODO
static ccol_status_t bench_ccol_dll_pop_front(size_t n) {
    return CCOL_STATUS_NOT_IMPLEMENTED;
}

//TODO
static ccol_status_t bench_ccol_dll_clone(size_t n) {
    return CCOL_STATUS_NOT_IMPLEMENTED;
}

//TODO
static ccol_status_t bench_ccol_dll_reverse(size_t n) {
    return CCOL_STATUS_NOT_IMPLEMENTED;
}

int main(void) {
    srand((unsigned int)time(NULL));

    bench_ccol_dll_push_back(ELEMENT_COUNT);
    // bench_ccol_dll_push_back(ELEMENT_COUNT);
    // bench_ccol_dll_push_front(ELEMENT_COUNT);
    // bench_ccol_dll_get(ELEMENT_COUNT);
    // bench_ccol_dll_contains(ELEMENT_COUNT);
    // bench_ccol_dll_pop_back(ELEMENT_COUNT);
    // bench_ccol_dll_pop_front(ELEMENT_COUNT);
    // bench_ccol_dll_clone(ELEMENT_COUNT);
    // bench_ccol_dll_reverse(ELEMENT_COUNT);
    return 0;
}