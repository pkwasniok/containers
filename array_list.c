#include "array_list.h"

#include <stdlib.h>
#include <string.h>

int array_list_init(array_list_t* this, size_t item_size, size_t capacity) {
    this->buffer = calloc(capacity, item_size);

    if (this->buffer == NULL)
        return CONTAINER_ERR_MEMORY;

    this->item_size = item_size;
    this->capacity = capacity;
    this->length = 0;

    return CONTAINER_OK;
}

int array_list_deinit(array_list_t* this) {
    if (this->buffer == NULL)
        return CONTAINER_ERR_INIT;

    free(this->buffer);
    this->buffer = NULL;

    return CONTAINER_OK;
}

int array_list_grow(array_list_t* this, size_t to_grow) {
    if (this->buffer == NULL)
        return CONTAINER_ERR_INIT;

    if (to_grow == 0)
        return CONTAINER_OK;

    size_t new_capacity = this->capacity + to_grow;
    void* new_buffer = realloc(this->buffer, this->item_size * new_capacity);

    if (new_buffer == NULL)
        return CONTAINER_ERR_MEMORY;

    this->buffer = new_buffer;
    this->capacity = new_capacity;

    return CONTAINER_OK;
}

int array_list_shrink(array_list_t* this, size_t to_shrink) {
    if (this->buffer == NULL)
        return CONTAINER_ERR_INIT;

    if (to_shrink == 0)
        return CONTAINER_OK;

    size_t new_capacity = (to_shrink >= this->capacity) ? (1) : (this->capacity - to_shrink);
    void* new_buffer = realloc(this->buffer, this->item_size * new_capacity);

    if (new_buffer == NULL)
        return CONTAINER_ERR_MEMORY;

    this->buffer = new_buffer;
    this->capacity = new_capacity;
    this->length = (new_capacity < this->length) ? (new_capacity) : (this->length);

    return CONTAINER_OK;
}

int array_list_push(array_list_t* this, void* item) {
    if (this->buffer == NULL)
        return CONTAINER_ERR_INIT;

    if (this->length == this->capacity)
        return CONTAINER_ERR_FULL;

    memcpy((this->buffer + (this->item_size * this->length)), item, this->item_size);
    this->length += 1;

    return CONTAINER_OK;
}

int array_list_pop(array_list_t* this, void* item) {
    if (this->buffer == NULL)
        return CONTAINER_ERR_INIT;

    if (this->length == 0)
        return CONTAINER_ERR_EMPTY;

    memcpy(item, this->buffer + (this->item_size * (this->length - 1)), this->item_size);
    this->length -= 1;

    return CONTAINER_OK;
}

