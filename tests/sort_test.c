//
// Created by xsy on 2024/7/30.
//
#include "sort.h"
#include <stdio.h>

static void* sort_arr[10];

#define set(index, i) \
    sort_arr[index] = &int##i

#define add(index,i) \
    int int##i = i; \
    set(index, i)

#define init_arr \
        add(0, 8);\
        add(1, 5);\
        add(2, 3);\
        add(3, 7);\
        add(4, 9);\
        add(5, 1);\
        add(6, 0);\
        add(7, 2);\
        add(8, 4);\
        add(9, 6);

#define reset_arr \
        set(0, 8);\
        set(1, 5);\
        set(2, 3);\
        set(3, 7);\
        set(4, 9);\
        set(5, 1);\
        set(6, 0);\
        set(7, 2);\
        set(8, 4);\
        set(9, 6);

static void print_arr()
{
    for (int i = 0; i < 10; ++i) {
        printf("%d ", *(int*)sort_arr[i]);
    }
    printf("\n");
}

static void bubble_test()
{
    bubble_sort(sort_arr, 10, int_compare, false);
    print_arr();
}

void sort_test()
{
#ifdef TEST_SORT
    init_arr
    bubble_test();
    reset_arr
#endif
}