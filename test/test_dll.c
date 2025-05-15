/*
 * ccol/test_dll.c
 *
 * dll unit tests
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stdlib.h>
#include <stdio.h>

#include "unity.h"
#include "dll.h"
#include "dll_internal.h"
#include "dll_iterator.h"

void setUp(void) {}
void tearDown(void) {}

void test_dll_create_stack(void) {
    dll_t doubly_linked_list;
    ccol_status_t status = dll_init(&doubly_linked_list, (copy_t){0}, (free_t){0}, (print_t){0}, (comparator_t){0});

    TEST_ASSERT_EQUAL(CCOL_STATUS_OK, status);
    TEST_ASSERT_TRUE(doubly_linked_list.is_initialized);
    TEST_ASSERT_EQUAL(0, doubly_linked_list.size);
    TEST_ASSERT_NULL(doubly_linked_list.head);
    TEST_ASSERT_NULL(doubly_linked_list.tail);

    dll_uninit(&doubly_linked_list);
}

void test_dll_create_heap(void) {
    dll_t *doubly_linked_list = NULL;
    ccol_status_t status = dll_create(&doubly_linked_list, (copy_t){0}, (free_t){0}, (print_t){0}, (comparator_t){0});

    TEST_ASSERT_EQUAL(CCOL_STATUS_OK, status);
    TEST_ASSERT_TRUE(doubly_linked_list->is_initialized);
    TEST_ASSERT_EQUAL(0, doubly_linked_list->size);
    TEST_ASSERT_NULL(doubly_linked_list->head);
    TEST_ASSERT_NULL(doubly_linked_list->tail);

    dll_destroy(doubly_linked_list);
}

int main(void) {
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_dll_create_stack);
    RUN_TEST(test_dll_create_heap);


    return UNITY_END();
}