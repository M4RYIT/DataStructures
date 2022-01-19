#pragma once

#include <stdlib.h>
#include <stdint.h>

static const size_t start_capacity = 5;
static const size_t capacity_inc = 4;
static const size_t capacity_dec = 3;
static const float rmv_perc = 0.6;
static const float add_perc = 0.5;

typedef struct dynarray
{
    size_t number_of_elements;
    size_t size_of_element;
    size_t capacity;
    uint8_t *data;
    uint8_t *tmp;
}
dynarray;

int dynarray_init(dynarray *array, const size_t size_of_element);

void dynarray_clear(dynarray *array);

int dynarray_append(dynarray *array, const void *value);

size_t dynarray_len(const dynarray *array);

int dynarray_get(const dynarray *array, const size_t index, void *value);

int dynarray_remove(dynarray *array, const size_t index);

float size_perc();