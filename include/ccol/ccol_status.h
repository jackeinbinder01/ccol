/*
 * ccol/ccol_status.h
 *
 * Return status codes for ccol functions.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#ifndef CCOL_STATUS_H
#define CCOL_STATUS_H

typedef enum ccol_status {
    CCOL_STATUS_OK = 0,
    CCOL_STATUS_ALLOC,
    CCOL_STATUS_UNINITIALIZED,
    CCOL_STATUS_INVALID_ARG,
    CCOL_STATUS_OUT_OF_BOUNDS,
    CCOL_STATUS_UNDERFLOW,
    CCOL_STATUS_OVERFLOW,
    CCOL_STATUS_NOT_FOUND,
    CCOL_STATUS_ALREADY_EXISTS,
    CCOL_STATUS_FULL,
    CCOL_STATUS_EMPTY,
    CCOL_STATUS_ERROR,
    CCOL_STATUS_HASH_FUNC,
    CCOL_STATUS_HASH_CTX,
    CCOL_STATUS_HASH_POLICY,
    CCOL_STATUS_COPY_FUNC,
    CCOL_STATUS_COPY_CTX,
    CCOL_STATUS_COPY,
    CCOL_STATUS_FREE_FUNC,
    CCOL_STATUS_FREE_CTX,
    CCOL_STATUS_PRINT_FUNC,
    CCOL_STATUS_PRINT_CTX,
    CCOL_STATUS_COMPARATOR_FUNC,
    CCOL_STATUS_COMPARATOR_CTX,
    CCOL_STATUS_KEY_SIZE,
    CCOL_STATUS_NOT_IMPLEMENTED,
} ccol_status_t;

static inline const char * ccol_status_to_string(ccol_status_t status) {
    switch (status) {
        case CCOL_STATUS_OK:              return "CCOL_STATUS_OK";
        case CCOL_STATUS_ALLOC:           return "CCOL_STATUS_ALLOC";
        case CCOL_STATUS_UNINITIALIZED:   return "CCOL_STATUS_UNINITIALIZED";
        case CCOL_STATUS_INVALID_ARG:     return "CCOL_STATUS_INVALID_ARG";
        case CCOL_STATUS_OUT_OF_BOUNDS:   return "CCOL_STATUS_OUT_OF_BOUNDS";
        case CCOL_STATUS_UNDERFLOW:       return "CCOL_STATUS_UNDERFLOW";
        case CCOL_STATUS_OVERFLOW:        return "CCOL_STATUS_OVERFLOW";
        case CCOL_STATUS_NOT_FOUND:       return "CCOL_STATUS_NOT_FOUND";
        case CCOL_STATUS_ALREADY_EXISTS:  return "CCOL_STATUS_ALREADY_EXISTS";
        case CCOL_STATUS_FULL:            return "CCOL_STATUS_FULL";
        case CCOL_STATUS_EMPTY:           return "CCOL_STATUS_EMPTY";
        case CCOL_STATUS_ERROR:           return "CCOL_STATUS_ERROR";
        case CCOL_STATUS_HASH_FUNC:       return "CCOL_STATUS_HASH_FUNC";
        case CCOL_STATUS_HASH_CTX:        return "CCOL_STATUS_HASH_CTX";
        case CCOL_STATUS_HASH_POLICY:     return "CCOL_STATUS_HASH_POLICY";
        case CCOL_STATUS_COPY_FUNC:       return "CCOL_STATUS_COPY_FUNC";
        case CCOL_STATUS_COPY_CTX:        return "CCOL_STATUS_COPY_CTX";
        case CCOL_STATUS_COPY:            return "CCOL_STATUS_COPY";
        case CCOL_STATUS_FREE_FUNC:       return "CCOL_STATUS_FREE_FUNC";
        case CCOL_STATUS_FREE_CTX:        return "CCOL_STATUS_FREE_CTX";
        case CCOL_STATUS_PRINT_FUNC:      return "CCOL_STATUS_PRINT_FUNC";
        case CCOL_STATUS_PRINT_CTX:       return "CCOL_STATUS_PRINT_CTX";
        case CCOL_STATUS_COMPARATOR_FUNC: return "CCOL_STATUS_COMPARATOR_FUNC";
        case CCOL_STATUS_COMPARATOR_CTX:  return "CCOL_STATUS_COMPARATOR_CTX";
        case CCOL_STATUS_KEY_SIZE:        return "CCOL_STATUS_KEY_SIZE";
        case CCOL_STATUS_NOT_IMPLEMENTED: return "CCOL_STATUS_NOT_IMPLEMENTED";
        default:                          return "INVALID";
    }
}

const char *ccol_strstatus(ccol_status_t status);

#endif  // CCOL_STATUS_H
