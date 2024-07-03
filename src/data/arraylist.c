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

bool arraylist_insert(arraylist * list, int index, ELE ele)
{
    if(index > list->size || index < 0)
    {
        perror( "Index out of bounds\n");
        return false;
    }

    //resize arraylist if necessary
    if(list->size == list->capacity)
    {
        if(!arraylist_resize(list, list->capacity << 1))
        {
            return false;
        }
    }

    //copy data
    for (int i = list->size; i > index; --i) {
        list->data[i] = list->data[i-1];
    }

    list->data[index] = ele;
    list->size++;
    return true;
}

void * arraylist_get(arraylist * list, int index)
{
    return list->data[index];
}

void * arraylist_remove(arraylist * list, int index)
{
    if (index >= list->size || index < 0)
    {
        perror( "Index out of bounds\n");
        return (void *) 0;
    }

    void * removed_ele = list->data[index];

    for (size_t i = index; i < list->size - 1; ++i)
    {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
    if (list->size > 0 && list->size <= (list->capacity >> 2))
    {
        arraylist_resize(list, list->capacity >> 1);
    }

    return removed_ele;
}

int arraylist_indexof(arraylist * list, ELE ele)
{
    for (int i = 0; i < list->size; ++i) {
        if(ele == list->data[i])
        {
            return i;
        }
    }
    return -1;
}

void arraylist_foreach(arraylist * list, ARRAY_FOREACH func)
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
