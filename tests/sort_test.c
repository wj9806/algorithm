//
// Created by xsy on 2024/7/30.
//
#include "sort.h"
#include <stdio.h>

static int sort_arr_len = 11;

static void* sort_arr[11];

static bool sort = true;

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
        __add(9, 6);\
        int int10 = 3;\
        __set(10, 10);

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
        __set(9, 6);\
        __set(10, 10);

static void print_arr()
{
    for (int i = 0; i < 10; ++i) {
        printf("%d ", *(int*)sort_arr[i]);
    }
    printf("\n");
}

#define _call_sort(_func_, nature) \
    printf("%20s: ", #_func_);\
    _func_(sort_arr, sort_arr_len, int_compare, nature);\
    print_arr();\
    __reset_arr

static void count_test() {
    int count[11] = {2,3,5,8,-3,7,9,-1,3,4};
    counting_sort(count, 11, sort);

    printf("%20s: ", "counting_sort");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", count[i]);
    }
    printf("\n");
}

void sort_test()
{
#ifdef TEST_SORT
    __init_arr
    _call_sort(bubble_sort, sort)
    _call_sort(selection_sort, sort)
    _call_sort(heap_sort, sort)
    _call_sort(insertion_sort, sort)
    _call_sort(shell_sort, sort)
    _call_sort(merge_sort, sort)
    _call_sort(merge_insertion_sort, sort)
    _call_sort(quick_sort, sort)
    count_test();
#endif
}