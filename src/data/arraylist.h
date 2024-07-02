//
// Created by wj on 2024/7/2.
//

#ifndef ALGORITHM_ARRAYLIST_H
#define ALGORITHM_ARRAYLIST_H

#include "common.h"

#define ELE void*

typedef struct {
    /** the arraylist capacity */
    int capacity;
    /** the arraylist size */
    int size;
    /** data array */
    ELE * data;
} arraylist;

typedef void (*func) (ELE);

/**
 * init given capacity's arraylist
 */
arraylist * arraylist_init(int capacity);

/**
 * add element into arraylist
 */
bool arraylist_add(arraylist * list, ELE ele);

/**
 * Iterate through the arraylist following the given function
 */
void arraylist_foreach(arraylist * list, func func);

/**
 * destroy the arraylist
 * @param list
 */
void arraylist_destroy(arraylist * list);

/**
 * get the given index's element
 */
void * arraylist_get(arraylist * list, int index);

/**
 * get arraylist size
 * @param list
 * @return
 */
static inline int arraylist_size(arraylist * list)
{
    return list->size;
}

/**
 * get arraylist capacity
 */
static inline int arraylist_capacity(arraylist * list)
{
    return list->capacity;
}

/** convert ele to given TYPE */
#define arraylist_get_bytype(list, index, TYPE) \
            (TYPE*)arraylist_get(list, index)

#endif //ALGORITHM_ARRAYLIST_H
