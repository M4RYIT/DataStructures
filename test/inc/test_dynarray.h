#include "clove.h"
#include "dynarray.h"

CLOVE_TEST(Dynarray_Init)
{
    dynarray arr;
    
    CLOVE_INT_EQ(0, dynarray_init(&arr, sizeof(int)));
}

CLOVE_TEST(Dynarray_InitNull)
{
    CLOVE_INT_EQ(-1, dynarray_init(NULL, sizeof(int)));
}

CLOVE_TEST(Dynarray_AppendValue)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    int a = 5;

    CLOVE_INT_EQ(0, dynarray_append(&arr, &a));
    CLOVE_INT_EQ(5, ((int*)arr.data)[0]);
}

CLOVE_TEST(Dynarray_AppendValues)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    int a = 1;
    int b = 2;
    int c = 3;

    CLOVE_INT_EQ(0, dynarray_append(&arr, &a));
    CLOVE_INT_EQ(0, dynarray_append(&arr, &b));
    CLOVE_INT_EQ(0, dynarray_append(&arr, &c));

    CLOVE_INT_EQ(a, ((int*)arr.data)[0]);
    CLOVE_INT_EQ(b, ((int*)arr.data)[1]);
    CLOVE_INT_EQ(c, ((int*)arr.data)[2]);

    CLOVE_INT_EQ(3, arr.number_of_elements);
}

CLOVE_TEST(Dynarray_AppendCapacityInc)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    int a = 5;

    dynarray_append(&arr, &a);
    dynarray_append(&arr, &a);
    dynarray_append(&arr, &a);
    dynarray_append(&arr, &a);

    CLOVE_INT_EQ(arr.capacity, 9);
    CLOVE_INT_EQ(4, arr.number_of_elements);
}

CLOVE_TEST(Dynarray_LenZero)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    CLOVE_INT_EQ(0, dynarray_len(&arr));
}

CLOVE_TEST(Dynarray_Len)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    int a = 5;
    dynarray_append(&arr, &a);
    dynarray_append(&arr, &a);

    CLOVE_INT_EQ(2, dynarray_len(&arr));
}

CLOVE_TEST(Dynarray_GetOffRange)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    int a = 5;
    dynarray_append(&arr, &a);

    int value;
    CLOVE_INT_EQ(-1, dynarray_get(&arr, -1, &value));
    CLOVE_INT_EQ(-1, dynarray_get(&arr, 2, &value));
}

CLOVE_TEST(Dynarray_Get)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    int a = 5;
    int b = 6;
    dynarray_append(&arr, &a);
    dynarray_append(&arr, &b);

    int value;
    CLOVE_INT_EQ(0, dynarray_get(&arr, 0, &value));
    CLOVE_INT_EQ(a, value);

    CLOVE_INT_EQ(0, dynarray_get(&arr, 1, &value));
    CLOVE_INT_EQ(b, value);
}

CLOVE_TEST(Dynarray_RemoveOffRange)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    int a = 5;
    dynarray_append(&arr, &a);

    CLOVE_INT_EQ(-1, dynarray_remove(&arr, -1));
    CLOVE_INT_EQ(-1, dynarray_remove(&arr, 2));
    CLOVE_INT_EQ(1, arr.number_of_elements);

    int value;    
    CLOVE_INT_EQ(0, dynarray_get(&arr, 0, &value));
    CLOVE_INT_EQ(a, value);
}

CLOVE_TEST(Dynarray_Remove)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    int a = 5;
    int b = 6;
    int c = 7;
    dynarray_append(&arr, &a);
    dynarray_append(&arr, &b);
    dynarray_append(&arr, &c);

    CLOVE_INT_EQ(0, dynarray_remove(&arr, 1));
    CLOVE_INT_EQ(2, arr.number_of_elements);
    
    int value;
    dynarray_get(&arr, 0, &value);
    CLOVE_INT_EQ(a, value);

    dynarray_get(&arr, 1, &value);
    CLOVE_INT_EQ(c, value);
}

CLOVE_TEST(Dynarray_RemoveCapacityDec)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    int a = 5;
    int b = 6;
    int c = 7;
    dynarray_append(&arr, &a);
    dynarray_append(&arr, &b);
    dynarray_append(&arr, &c);

    CLOVE_INT_EQ(0, dynarray_remove(&arr, 0));
    CLOVE_INT_EQ(0, dynarray_remove(&arr, 0));
    CLOVE_INT_EQ(2, arr.capacity);
    CLOVE_INT_EQ(1, arr.number_of_elements);
}

CLOVE_TEST(Dynarray_Clear)
{
    dynarray arr;
    dynarray_init(&arr, sizeof(int));

    int a = 5;
    dynarray_append(&arr, &a);

    dynarray_clear(&arr);

    CLOVE_INT_EQ(0, arr.number_of_elements);
    CLOVE_NULL(arr.data);
}

CLOVE_SUITE(DynarraySuite)
{
    CLOVE_SUITE_TESTS(Dynarray_Init, Dynarray_InitNull, Dynarray_AppendValue, Dynarray_AppendCapacityInc, 
                      Dynarray_AppendValues, Dynarray_LenZero, Dynarray_Len, Dynarray_GetOffRange, Dynarray_Get, 
                      Dynarray_RemoveOffRange, Dynarray_Remove, Dynarray_RemoveCapacityDec, Dynarray_Clear);
}