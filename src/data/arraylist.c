//
// Created by wj on 2024/7/2.
//

#include "arraylist.h"
#include <stdlib.h>

arraylist * arraylist_init(int capacity)
{
    arraylist * list = malloc_type(arraylist);
    if (!list) {
        perror("Failed to create arraylist");
        return (arraylist *) 0;
    }

    list->capacity = capacity;
    list->size = 0;

    list->data = malloc_size_type(capacity, ELE);
    if (!list->data) {
        perror("Failed to allocate data array");
        free(list);
        return (arraylist *) 0;
    }

    return list;
}

/**
 * resize arraylist
 */
static bool arraylist_resize(arraylist * list, int capacity)
{
    ELE* data = realloc_size_type(list->data, capacity, ELE);
    if (!data) {
        perror("Failed to resize data array");
        return false;
    }
    list->data = data;
    list->capacity = capacity;
    return true;
}

bool arraylist_add(arraylist * list, ELE ele)
{
    if(list->size >= list->capacity)
    {
        if(!arraylist_resize(list, list->capacity << 1))
        {
            return false;
        }
    }
    list->data[list->size++] = ele;
    return true;
}

void * arraylist_get(arraylist * list, int index)
{
    return list->data[index];
}

void arraylist_foreach(arraylist * list, func func)
{
    for (int i = 0; i < list->size; ++i) {
        func(list->data[i]);
    }
}

void arraylist_destroy(arraylist * list)
{
    free(list->data);
    free(list);
}
