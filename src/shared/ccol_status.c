/*
 * ccol/ccol_status.c
 *
 *
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include "ccol_status.h"

const char *ccol_strstatus(ccol_status_t status) {
    switch (status) {
        case CCOL_STATUS_OK:              return "Success";
        case CCOL_STATUS_ALLOC:           return "Memory allocation failed";
        case CCOL_STATUS_UNINITIALIZED:   return "Object is not initialized";
        case CCOL_STATUS_INVALID_ARG:     return "Invalid argument";
        case CCOL_STATUS_OUT_OF_BOUNDS:   return "Index out of bounds";
        case CCOL_STATUS_UNDERFLOW:       return "Index underflow";
        case CCOL_STATUS_OVERFLOW:        return "Index overflow";
        case CCOL_STATUS_NOT_FOUND:       return "Element not found in container";
        case CCOL_STATUS_FULL:            return "Container is full";
        case CCOL_STATUS_EMPTY:           return "Container is empty";
        case CCOL_STATUS_ERROR:           return "Generic error";
        default:                          return "Unknown error";
    }
}
