//
// Created by xsy on 2024/7/30.
//

#include "sort.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void shell_sort(void* data[], int arr_len, compare cp, bool nature_sort)
{
    for (int gap = arr_len >> 1; gap >= 1; gap = gap >> 1)
    {
        for (int low = gap; low < arr_len; ++low)
        {
            void * t = data[low];
            int i = low - gap;
            if(nature_sort) {
                while (i >= 0 && cp(t, data[i]) < 0)
                {
                    data[i + gap] = data[i];
                    i -= gap;
                }
            }
            else
            {
                while (i >= 0 && cp(t, data[i]) > 0)
                {
                    data[i + gap] = data[i];
                    i -= gap;
                }
            }

            if(i != low - gap)
                data[i + gap] = t;
        }
    }
}

void monkey_sort(void* data[], int arr_len, compare cp, bool nature_sort)
{
    int cnt = 0;
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned)time(NULL));
        initialized = 1;
    }
    while (true)
    {
        for (int i = 0; i < arr_len; i++)
            swap(data, i, rand() % arr_len);
        cnt++;
        if (is_ordered(data, arr_len, cp, nature_sort))
        {
            debug_info("monkey_sort count: %d", cnt);
            return;
        }
    }
}

static void merge(void* a1[], int i, int i_end, int j, int j_end, void* a2[], compare cp, bool nature_sort)
{
    int k = i;
    while (i <= i_end && j <= j_end)
    {
        if (nature_sort)
        {
            if (cp(a1[i], a1[j]) < 0)
                a2[k] = a1[i++];
            else
                a2[k] = a1[j++];

            k++;
        }
        else
        {
            if (cp(a1[i], a1[j]) > 0)
                a2[k] = a1[i++];
            else
                a2[k] = a1[j++];

            k++;
        }
    }

    if (i > i_end)
    {
        size_t move_size = (j_end - j + 1) * sizeof(void*);
        memmove(a2 + k, a1 + j, move_size);
    }
    if (j > j_end)
    {
        size_t move_size = (i_end - i + 1) * sizeof(void*);
        memmove(a2 + k, a1 + i, move_size);
    }

}

static void split(void* data[], int left, int right, compare cp, bool nature_sort, void* data2[])
{
    if (left == right) return;

    int m = (left + right) >> 1;
    split(data, left, m, cp, nature_sort, data2);
    split(data, m + 1, right, cp, nature_sort, data2);

    merge(data, left, m, m + 1, right, data2, cp, nature_sort);

    size_t move_size = (right - left + 1) * sizeof(void*);
    memmove(data + left, data2 + left, move_size);
}

void merge_sort(void* data[], int arr_len, compare cp, bool nature_sort)
{
    void* data2[arr_len];
    split(data, 0, arr_len - 1, cp, nature_sort, data2);
}

static void _insertion_sort(void* data[], int left, int right, compare cp, bool nature_sort)
{
    for (int low = left + 1; low <= right; ++low) {
        void * t = data[low];
        int i = low - 1;
        if(nature_sort) {
            while (i >= left && cp(t, data[i]) < 0)
            {
                data[i + 1] = data[i];
                i--;
            }
        }
        else
        {
            while (i >= left && cp(t, data[i]) > 0)
            {
                data[i + 1] = data[i];
                i--;
            }
        }

        if(i != low - 1)
            data[i + 1] = t;
    }
}

static void insertion_or_split(void* data[], int left, int right, compare cp, bool nature_sort, void* data2[])
{
    if (right - left <= 32)
    {
        _insertion_sort(data, left, right, cp, nature_sort);
        return;
    }

    int m = (left + right) >> 1;
    insertion_or_split(data, left, m, cp, nature_sort, data2);
    insertion_or_split(data, m + 1, right, cp, nature_sort, data2);

    merge(data, left, m, m + 1, right, data2, cp, nature_sort);

    size_t move_size = (right - left + 1) * sizeof(void*);
    memmove(data + left, data2 + left, move_size);
}

void merge_insertion_sort(void* data[], int arr_len, compare cp, bool nature_sort)
{
    void* data2[arr_len];
    insertion_or_split(data, 0, arr_len - 1, cp, nature_sort, data2);
}

static int rand_int(int left, int right) {
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned)time(NULL));
        initialized = 1;
    }
    int range = right - left + 1;
    return left + rand() % range;
}

static int partition(void * data[], int left, int right, compare cp, bool nature_sort)
{
    int idx = rand_int(left, right);
    swap(data, idx, left);

    void * pv = data[left];
    int i = left + 1, j = right;
    while (i <= j)
    {
        if (nature_sort) {
            while (i <= j && cp(data[i], pv) < 0)
                i++;
            while (i <= j && cp(data[j], pv) > 0)
                j--;
        }
        else
        {
            while (i <= j && cp(data[i], pv) > 0)
                i++;
            while (i <= j && cp(data[j], pv) < 0)
                j--;
        }
        if (i <= j)
            swap(data, i++, j--);
    }

    swap(data, left, j);
    return j;
}

static void quick(void * data[], int left, int right, compare cp, bool nature_sort)
{
    if(left >= right) return;
    int p = partition(data, left, right, cp, nature_sort);
    quick(data, left, p - 1, cp, nature_sort);
    quick(data, p + 1, right, cp, nature_sort);
}

void quick_sort(void* data[], int arr_len, compare cp, bool nature_sort)
{
    quick(data, 0, arr_len - 1, cp, nature_sort);
}

void counting_sort(int data[], int arr_len, bool nature_sort)
{
    if (arr_len <= 0) return;

    int max = data[0], min = data[0];
    for (int i = 0; i < arr_len; ++i)
    {
        if (data[i] > max)
            max = data[i];
        if (data[i] < min)
            min = data[i];
    }

    int range = max - min + 1;
    int count[range];
    memset(count, 0, sizeof(count));

    for (int i = 0; i < arr_len; ++i)
        count[data[i] - min]++;

    int k = 0;
    if (nature_sort)
    {
        for (int i = 0; i < range; ++i) {
            while (count[i]) {
                data[k++] = i + min;
                count[i]--;
            }
        }
    }
    else
    {
        for (int i = range - 1; i > 0; --i) {
            while (count[i]) {
                data[k++] = i + min;
                count[i]--;
            }
        }
    }
}