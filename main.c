#include <stdio.h>
#include "array_list.h"

#include <stdint.h>
#include <assert.h>

int main(void) {
    int res;

    array_list_t list;

    res = array_list_init(&list, 2, 32);

    printf("length: %d, capacity: %d\n", list.length, list.capacity);

    for (uint16_t i = 1; i <= 32; i++) {
        res = array_list_push(&list, &i);
        assert(res == CONTAINER_OK);
    }

    printf("length: %d, capacity: %d\n", list.length, list.capacity);

    array_list_shrink(&list, 16);

    printf("length: %d, capacity: %d\n", list.length, list.capacity);

    for (uint16_t item, i = 1; i <= 16; i++) {
        res = array_list_pop(&list, &item);
        assert(res == CONTAINER_OK);

        printf("%d\n", item);
    }

    array_list_deinit(&list);

    return 0;
}

