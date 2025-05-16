/*
 * ccol/timer.h
 *
 * Timer for benchmarking.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef TIMER_H
#define TIMER_H

#include "timer_platform.h"

typedef enum time_scale {
    TIME_SCALE_SECONDS,
    TIME_SCALE_DECISECONDS,
    TIME_SCALE_CENTISECONDS,
    TIME_SCALE_MILLISECONDS,
    TIME_SCALE_MICROSECONDS,
    TIME_SCALE_NANOSECONDS
} time_scale_t;

typedef struct timer {
    struct timespec start;
} timer_t;

static inline const char *time_scale_unit_to_string(time_scale_t time_scale) {
    switch(time_scale) {
        case TIME_SCALE_SECONDS:         return "s";
        case TIME_SCALE_DECISECONDS:     return "ds";
        case TIME_SCALE_CENTISECONDS:    return "cs";
        case TIME_SCALE_MILLISECONDS:    return "ms";
        case TIME_SCALE_MICROSECONDS:    return "µs";
        case TIME_SCALE_NANOSECONDS:     return "ns";
        default:                         return "invalid time-scale";
    }
}

static inline double time_scale_multiplier(time_scale_t time_scale) {
    switch(time_scale) {
        case TIME_SCALE_SECONDS:         return 1.0;
        case TIME_SCALE_DECISECONDS:     return 1e1;
        case TIME_SCALE_CENTISECONDS:    return 1e2;
        case TIME_SCALE_MILLISECONDS:    return 1e3;
        case TIME_SCALE_MICROSECONDS:    return 1e6;
        case TIME_SCALE_NANOSECONDS:     return 1e9;
        default:                         return -1.0;
    }
}

static inline double time_scale_convert(double value, time_scale_t from, time_scale_t to) {
    double from_multiplier = time_scale_multiplier(from);
    double to_multiplier = time_scale_multiplier(to);
    if (from_multiplier <= 0 || to_multiplier <= 0) return -1.0;
    return value * (from_multiplier / to_multiplier);
}

static inline void start_timer(timer_t *timer) {
    clock_gettime(CLOCK_MONOTONIC, &timer->start);
}

static inline double stop_timer(const timer_t *timer, time_scale_t time_scale) {
    struct timespec timer_end_time;
    clock_gettime(CLOCK_MONOTONIC, &timer_end_time);

    double sec_elapsed =
        (timer_end_time.tv_sec - timer->start.tv_sec) +
        (timer_end_time.tv_nsec - timer->start.tv_nsec) / 1e9;

    return sec_elapsed * time_scale_multiplier(time_scale);
}

#endif //TIMER_H
