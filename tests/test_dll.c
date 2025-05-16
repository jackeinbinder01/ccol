/*
 * tests/test_ccol_dll.c
 *
 * Doubly-linked list (dll) dll unit tests.
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdio.h>

#include "unity.h"
#include "ccol/ccol_dll.h"
#include "ccol/ccol_dll_iterator.h"
#include "src/dll/internal.h"

void setUp(void) {}
void tearDown(void) {}

void test_ccol_dll_create_stack(void) {
    ccol_dll_t list;
    ccol_status_t status = ccol_dll_init(
        &list,
        (ccol_copy_t){0},
        (ccol_free_t){0},
        (ccol_print_t){0},
        (ccol_comparator_t){0}
    );

    TEST_ASSERT_EQUAL(CCOL_STATUS_OK, status);
    TEST_ASSERT_TRUE(list.is_initialized);
    TEST_ASSERT_EQUAL(0, list.size);
    TEST_ASSERT_NULL(list.head);
    TEST_ASSERT_NULL(list.tail);

    ccol_dll_uninit(&list);
}

void test_ccol_dll_create_heap(void) {
    ccol_dll_t *list = NULL;
    ccol_status_t status = ccol_dll_create(
        &list,
        (ccol_copy_t){0},
        (ccol_free_t){0},
        (ccol_print_t){0},
        (ccol_comparator_t){0}
    );

    TEST_ASSERT_EQUAL(CCOL_STATUS_OK, status);
    TEST_ASSERT_TRUE(list->is_initialized);
    TEST_ASSERT_EQUAL(0, list->size);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);

    ccol_dll_destroy(list);
}

int main(void) {
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_ccol_dll_create_stack);
    RUN_TEST(test_ccol_dll_create_heap);

    return UNITY_END();
}