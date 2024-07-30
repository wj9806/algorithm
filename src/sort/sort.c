//
// Created by xsy on 2024/7/30.
//

#include "sort.h"

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
                {
                    void * tmp = data[i];
                    data[i] = data[i + 1];
                    data[i + 1] = tmp;
                }
                x = i;
            }
            else
            {
                if(cp(data[i], data[i+1]) < 0)
                {
                    void * tmp = data[i];
                    data[i] = data[i + 1];
                    data[i + 1] = tmp;
                }
                x = i;
            }
        }
        j = x;
    }
}

