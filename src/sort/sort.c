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

static void heapify(void* data[], int n, int i, compare cp)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && cp(data[left], data[largest]) > 0)
        largest = left;

    if(right < n && cp(data[right], data[largest]) > 0)
        largest = right;

    if(largest != i)
    {
        swap(data, i, largest);
        heapify(data, n, largest, cp);
    }
}

static void build_heap(void* data[], int n, compare cp)
{
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(data, n, i, cp);
}

void heap_sort(void* data[], int arr_len, compare cp, bool nature_sort)
{
    build_heap(data, arr_len, cp);

    for(int i = arr_len - 1; i > 0; i--)
    {
        swap(data, 0, i);
        heapify(data, i, 0, cp);
    }

    if(!nature_sort)
    {
        for (int i = 0; i < arr_len / 2; i++)
            swap(data, i, arr_len - 1 - i);
    }
}

void insertion_sort(void* data[], int arr_len, compare cp, bool nature_sort)
{
    for (int low = 0; low < arr_len; ++low) {
        void * t = data[low];
        int i = low - 1;
        if(nature_sort) {
            while (i >= 0 && cp(t, data[i]) < 0)
            {
                data[i + 1] = data[i];
                i--;
            }
        }
        else
        {
            while (i >= 0 && cp(t, data[i]) > 0)
            {
                data[i + 1] = data[i];
                i--;
            }
        }

        if(i != low - 1)
            data[i + 1] = t;
    }
}