//
// Created by xsy on 2024/7/30.
//

#include "sort.h"

static void swap(void* data[], int i, int j)
{
    void * tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
}

void bubble_sort(void* data[], int arr_len, compare cp, bool nature_sort)
{
    int j = arr_len - 1;
    while(j)
    {
        int x = 0;
        for (int i = 0; i < j; ++i) {
            if(nature_sort)
            {
                if(cp(data[i], data[i+1]) > 0)
                    swap(data, i, i + 1);
                x = i;
            }
            else
            {
                if(cp(data[i], data[i+1]) < 0)
                    swap(data, i, i + 1);
                x = i;
            }
        }
        j = x;
    }
}

void selection_sort(void* data[], int arr_len, compare cp, bool nature_sort)
{
    for (int right = arr_len - 1; right > 0; --right) {
        int candidate = right;
        for (int i = 0; i < right; ++i) {
            if(nature_sort)
            {
                if(cp(data[i], data[candidate]) > 0)
                    candidate = i;
            }
            else
            {
                if(cp(data[i], data[candidate]) < 0)
                    candidate = i;
            }
        }
        if(candidate != right)
            swap(data, candidate, right);
    }
}

