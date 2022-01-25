#include <stdio.h>
#include <string.h>
#include "dynarray.h"
#include "ds_utils.h"

float size_perc(const dynarray *array)
{
    return array->number_of_elements/(float)array->capacity;
}

int dynarray_init(dynarray *array, const size_t size_of_element)
{
    if (!array)
    {
        puts("Null array");
        return -1;
    }

    array->number_of_elements = 0;
    array->size_of_element = size_of_element;
    array->capacity = start_capacity;
    array->data = malloc(array->capacity*size_of_element);
    if (!array->data)
    {
        puts("Data allocation failure");
        return -1;
    }

    array->tmp = malloc(size_of_element);
    if (!array->tmp)
    {
        free(array->data);
        puts("Temp data allocation failed");
        return -1;
    }

    return 0;
}

void dynarray_clear(dynarray *array)
{
    array->number_of_elements = 0;
    array->size_of_element = 0;
    free(array->data);
    array->data = NULL;
    free(array->tmp);
    array->tmp = NULL;
}

int dynarray_append(dynarray *array, const void *value)
{
    const size_t new_dim = array->number_of_elements + 1;

    if (size_perc(array)>=add_perc)
    {
        const size_t new_cap = array->capacity + capacity_inc; 
        uint8_t *new_data = realloc(array->data, new_cap * array->size_of_element);

        if (!new_data)
        {
            puts("Append failure");
            return -1;
        }

        array->data = new_data;
        array->capacity = new_cap;
    }    

    size_t offset = array->number_of_elements * array->size_of_element;
    memcpy(array->data + offset, value, array->size_of_element);
    array->number_of_elements = new_dim;

    return 0;
}

size_t dynarray_len(const dynarray *array)
{
    return array->number_of_elements;
}

int dynarray_get(const dynarray *array, const size_t index, void *value)
{
    if (index >= array->number_of_elements)
    {
        puts("Invalid index");
        return -1;
    }

    const size_t offset = index * array->size_of_element;
    memcpy(value, array->data+offset, array->size_of_element);
    return 0;
}

int dynarray_remove(dynarray *array, const size_t index)
{
    if (index >= array->number_of_elements)
    {
        puts("Invalid index");
        return -1;
    }

    const size_t offset = index * array->size_of_element;
    const size_t new_dim = array->number_of_elements - 1;

    if (index < new_dim)
    {
        memcpy(array->tmp, array->data + offset, array->size_of_element);
        memmove(array->data + offset, array->data + offset + array->size_of_element, (array->number_of_elements-index)*array->size_of_element);
    }
        
    if (size_perc(array)<=rmv_perc)
    {
        const size_t new_cap = array->capacity - capacity_dec; 
        uint8_t *new_data = realloc(array->data, new_cap * array->size_of_element);

        if (!new_data)
        {
            if (index < new_dim)
            {
                memmove(array->data + offset + array->size_of_element, array->data + offset, (array->number_of_elements-index)*array->size_of_element);
                memcpy(array->data + offset, array->tmp, array->size_of_element);
            }

            puts("Remove failure");
            return -1;
        }

        array->data = new_data;
        array->capacity = new_cap;
    }

    array->number_of_elements = new_dim;

    return 0;
}
