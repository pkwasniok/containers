#pragma once

#include <stdio.h>

#define CONTAINER_OK         0
#define CONTAINER_ERR_INIT   1
#define CONTAINER_ERR_MEMORY 2
#define CONTAINER_ERR_FULL   3
#define CONTAINER_ERR_EMPTY  4

typedef struct {
    void* buffer;
    size_t item_size;
    size_t capacity;
    size_t length;
} array_list_t;

int array_list_init(array_list_t*, size_t item_size, size_t capacity);
int array_list_deinit(array_list_t*);

int array_list_grow(array_list_t*, size_t to_grow);
int array_list_shrink(array_list_t*, size_t to_shrink);

int array_list_push(array_list_t*, void*);
int array_list_pop(array_list_t*, void*);

