/*
 * ccol/bench_utils.h
 *
 * Benchmarking utilities.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */
#ifndef BENCH_UTILS_H
#define BENCH_UTILS_H

#include <stdio.h>
#include "timer.h"

#define PRINT_BENCH(label, num_elements, elapsed, time_scale)              \
    do {                                                                   \
        const char *unit = time_scale_unit_to_string(time_scale);          \
        printf("[%s]\n", label);                                           \
        printf("    %-20s %d\n", "Elements:", (int)(num_elements));        \
        printf("    %-20s %.2f %s\n", "Time elapsed:", elapsed, unit);     \
        printf("    %-20s %.2f ops/sec\n", "Throughput:",                  \
            elapsed > 0.0 ? (num_elements / (elapsed / 1000.0)) : 0.0);    \
    } while (0)

#endif //BENCH_UTILS_H
