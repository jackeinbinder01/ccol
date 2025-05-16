/*
 * ccol/timer_platform.h
 *
 * Enable cross-platform compatibility (Unix, Linux & Windows).
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef TIMER_PLATFORM_H
#define TIMER_PLATFORM_H

#ifdef _WIN32
#include <windows.h>

// Only define timespec if not already provided
#if !defined(HAVE_STRUCT_TIMESPEC) && !defined(_TIMESPEC_DEFINED)
#define _TIMESPEC_DEFINED
struct timespec {
    time_t tv_sec;
    long tv_nsec;
};
#endif

// Only define clock_gettime if not available
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1

static inline int clock_gettime(int unused, struct timespec* t) {
    static LARGE_INTEGER frequency;
    static BOOL initialized = FALSE;
    LARGE_INTEGER counter;

    if (!initialized) {
        if (!QueryPerformanceFrequency(&frequency)) return -1;
        initialized = TRUE;
    }

    if (!QueryPerformanceCounter(&counter)) return -1;

    t->tv_sec = (time_t)(counter.QuadPart / frequency.QuadPart);
    t->tv_nsec = (long)(((counter.QuadPart % frequency.QuadPart) * 1e9) / frequency.QuadPart);
    return 0;
}

#endif // CLOCK_MONOTONIC

#else
#include <time.h>
#endif

#endif // TIMER_PLATFORM_H
