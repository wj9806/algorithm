//
// Created by xsy on 2024/7/30.
//
#include "sort.h"
#include <stdio.h>

static void* sort_arr[10];

#define __set(index, i) \
    sort_arr[index] = &int##i

#define __add(index,i) \
    int int##i = i; \
    __set(index, i)

#define __init_arr \
        __add(0, 8);\
        __add(1, 5);\
        __add(2, 3);\
        __add(3, 7);\
        __add(4, 9);\
        __add(5, 1);\
        __add(6, 0);\
        __add(7, 2);\
        __add(8, 4);\
        __add(9, 6);

#define __reset_arr \
        __set(0, 8);\
        __set(1, 5);\
        __set(2, 3);\
        __set(3, 7);\
        __set(4, 9);\
        __set(5, 1);\
        __set(6, 0);\
        __set(7, 2);\
        __set(8, 4);\
        __set(9, 6);

static void print_arr()
{
    for (int i = 0; i < 10; ++i) {
        printf("%d ", *(int*)sort_arr[i]);
    }
    printf("\n");
}

#define _call_sort(_func_, nature) \
    printf("%s: ", #_func_);\
    _func_(sort_arr, 10, int_compare, nature);\
    print_arr();\
    __reset_arr

void sort_test()
{
#ifdef TEST_SORT
    __init_arr
    _call_sort(bubble_sort, true);
    _call_sort(selection_sort, true);
    _call_sort(heap_sort, false);
    _call_sort(insertion_sort, true);
    _call_sort(shell_sort, false);
    _call_sort(monkey_sort, true);
#endif
}