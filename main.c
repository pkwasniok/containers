#include <stdio.h>
#include "array_list.h"

#include <stdint.h>
#include <assert.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_init(void) {
    array_list_t list;

    CU_ASSERT(array_list_init(&list, 1, 16) == CONTAINER_OK);

    CU_ASSERT(list.buffer != NULL);
    CU_ASSERT(list.item_size == 1);
    CU_ASSERT(list.capacity == 16);
    CU_ASSERT(list.length == 0)

    array_list_deinit(&list);
}

void test_deinit(void) {
    array_list_t list;
    array_list_init(&list, 1, 16);

    CU_ASSERT(array_list_deinit(&list) == CONTAINER_OK);
}

void test_grow(void) {
    array_list_t list;
    array_list_init(&list, 1, 16);

    CU_ASSERT(array_list_grow(&list, 16) == CONTAINER_OK);

    CU_ASSERT(list.capacity == 32);
}

void test_shrink_empty(void) {
    array_list_t list;
    array_list_init(&list, 1, 16);

    CU_ASSERT(array_list_shrink(&list, 8) == CONTAINER_OK);
    CU_ASSERT(list.capacity == 8);
}

void test_shrink_full(void) {
    array_list_t list;
    array_list_init(&list, 1, 16);
    for (uint8_t i = 1; i <= 16; i++)
        array_list_push(&list, &i);

    CU_ASSERT(array_list_shrink(&list, 8) == CONTAINER_OK);
    CU_ASSERT(list.capacity == 8);
    CU_ASSERT(list.length == 8);
}

void test_shrink_over_capacity(void) {
    array_list_t list;
    array_list_init(&list, 1, 16);

    CU_ASSERT(array_list_shrink(&list, 32) == CONTAINER_OK);
    CU_ASSERT(list.capacity == 1);
}

int main(void) {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("ArrayList", 0, 0);
    CU_add_test(suite, "init", test_init);
    CU_add_test(suite, "deinit", test_deinit);
    CU_add_test(suite, "grow", test_grow);
    CU_add_test(suite, "shrink empty list", test_shrink_empty);
    CU_add_test(suite, "shrink full list", test_shrink_full);
    CU_add_test(suite, "shrink over capacity", test_shrink_over_capacity);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

