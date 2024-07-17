//
// Created by wj on 2024/7/2.
//

#ifndef ALGORITHM_ARRAYLIST_H
#define ALGORITHM_ARRAYLIST_H

#include "common.h"
#include "basetype_arraylist.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ support for struct~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

typedef struct {
    /** the arraylist capacity */
    int capacity;
    /** the arraylist size */
    int size;
    /** data array */
    ELE * data;
} arraylist;

typedef void (*ARRAY_FOREACH) (ELE);

/**
 * init given capacity's arraylist
 */
arraylist * arraylist_init(int capacity);

/**
 * Appends the specified element to the end of this list.
 */
bool arraylist_add(arraylist * list, ELE ele);

/**
 * Inserts the specified element at the specified position in this
 * list. Shifts the element currently at that position (if any) and
 * any subsequent elements to the right (adds one to their indices).
 */
bool arraylist_insert(arraylist * list, int index, ELE ele);

/**
 * Iterate through the arraylist following the given function
 */
void arraylist_foreach(arraylist * list, ARRAY_FOREACH func);

/**
 * destroy the arraylist
 * @param list
 */
void arraylist_destroy(arraylist * list);

/**
 * Returns the element at the specified position in this list.
 */
void * arraylist_get(arraylist * list, int index);

/**
 * Removes the element at the specified position in this list.
 */
void * arraylist_remove(arraylist * list, int index);

/**
 * Returns the index of the first occurrence of the specified element
 * in this list, or -1 if this list does not contain the element.
 */
int arraylist_indexof(arraylist * list, ELE ele);

/**
 * Returns true if this list contains the specified element
 */
static inline bool arraylist_contains(arraylist * list, ELE ele)
{
    return arraylist_indexof(list, ele) >= 0;
}

/**
 * Returns true if this list contains no elements.
 */
static inline bool arraylist_empty(arraylist * list)
{
    return list->size == 0;
}

/**
 * Returns arraylist size
 */
static inline int arraylist_size(arraylist * list)
{
    return list->size;
}

/**
 * Returns arraylist capacity
 */
static inline int arraylist_capacity(arraylist * list)
{
    return list->capacity;
}

/** convert ele to given TYPE */
#define arraylist_get_bytype(list, index, TYPE) \
            (TYPE*)arraylist_get(list, index)

#define arraylist_remove_bytype(list, index, TYPE) \
            (TYPE*)arraylist_remove(list, index)

#endif //ALGORITHM_ARRAYLIST_H
