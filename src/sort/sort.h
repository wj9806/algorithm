//
// Created by xsy on 2024/7/30.
//

#ifndef ALGORITHM_SORT_H
#define ALGORITHM_SORT_H

#include "common.h"

void bubble_sort(void* data[], int arr_len, compare cp, bool nature_sort);

void selection_sort(void* data[], int arr_len, compare cp, bool nature_sort);

void heap_sort(void* data[], int arr_len, compare cp, bool nature_sort);

void insertion_sort(void* data[], int arr_len, compare cp, bool nature_sort);

void shell_sort(void* data[], int arr_len, compare cp, bool nature_sort);

void monkey_sort(void* data[], int arr_len, compare cp, bool nature_sort);

void merge_sort(void* data[], int arr_len, compare cp, bool nature_sort);

#endif //ALGORITHM_SORT_H
