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
        case CCOL_STATUS_ALREADY_EXISTS:  return "Element already exists in container";
        case CCOL_STATUS_FULL:            return "Container is full";
        case CCOL_STATUS_EMPTY:           return "Container is empty";
        case CCOL_STATUS_ERROR:           return "Generic error";
        case CCOL_STATUS_HASH_FUNC:       return "Hash function not provided";
        case CCOL_STATUS_HASH_CTX:        return "Hash context not provided";
        case CCOL_STATUS_HASH_POLICY:     return "Invalid hash policy";
        case CCOL_STATUS_COPY_FUNC:       return "Copy function not provided";
        case CCOL_STATUS_COPY_CTX:        return "Copy context not provided";
        case CCOL_STATUS_FREE_FUNC:       return "Free function not provided";
        case CCOL_STATUS_FREE_CTX:        return "Free context not provided";
        case CCOL_STATUS_PRINT_FUNC:      return "Print function not provided";
        case CCOL_STATUS_PRINT_CTX:       return "Print context not provided";
        case CCOL_STATUS_COMPARATOR_FUNC: return "Comparator function not provided";
        case CCOL_STATUS_COMPARATOR_CTX:  return "Comparator context not provided";
        case CCOL_STATUS_KEY_SIZE:        return "Unsupported key size";
        default:                          return "Unknown error";
    }
}
