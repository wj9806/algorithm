//
// Created by wj on 2024/7/2.
//

#ifndef ALGORITHM_BASETYPE_ARRAYLIST_H
#define ALGORITHM_BASETYPE_ARRAYLIST_H

#include "common.h"
#include <stdlib.h>
#include <stdint.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ support for base type~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#define DECLARE_BASE_TYPE_ARRAYLIST(TYPE)   \
    typedef  void (*TYPE##_array_foreach)(TYPE ele);\
    typedef struct {                        \
        int capacity;                       \
        int size;                           \
        TYPE * data;                        \
    } TYPE##_arraylist;                     \
    TYPE##_arraylist * TYPE##_arraylist_init(int capacity);                                        \
    bool TYPE##_arraylist_add(TYPE##_arraylist * list, TYPE ele);                                  \
    bool TYPE##_arraylist_insert(TYPE##_arraylist * list, int index, TYPE ele);                    \
    void TYPE##_arraylist_foreach(TYPE##_arraylist * list, TYPE##_array_foreach func);             \
    void TYPE##_arraylist_destroy(TYPE##_arraylist * list);                                        \
    TYPE TYPE##_arraylist_get(TYPE##_arraylist * list, int index);                                 \
    TYPE TYPE##_arraylist_remove(TYPE##_arraylist * list, int index);                              \
    int TYPE##_arraylist_indexof(TYPE##_arraylist * list, TYPE ele);                               \
    static inline bool TYPE##_arraylist_contains(TYPE##_arraylist * list, TYPE ele)                \
    {\
        return TYPE##_arraylist_indexof(list, ele) >= 0;\
    }\
    static inline bool TYPE##_arraylist_empty(TYPE##_arraylist * list)\
    {\
        return list->size == 0;\
    }\
    static inline int TYPE##_arraylist_size(TYPE##_arraylist * list)\
    {\
        return list->size;\
    }\
    static inline int TYPE##_arraylist_capacity(TYPE##_arraylist * list)\
    {\
        return list->capacity;\
    }

#define DEFINITE_BASE_TYPE_ARRAYLIST(TYPE)\
    TYPE##_arraylist * TYPE##_arraylist_init(int capacity)\
    {\
        TYPE##_arraylist * list = malloc_type(TYPE##_arraylist);\
        if (!list) {\
            perror("Failed to create arraylist");\
            return (TYPE##_arraylist *) 0;\
        }\
        list->capacity = capacity;\
        list->size = 0;\
        list->data = malloc_size_type(capacity, TYPE);\
        if (!list->data) {\
            perror("Failed to allocate data array");\
            free(list);\
            return (TYPE##_arraylist *) 0;\
        }\
        return list;\
    }                                       \
    static bool TYPE##_arraylist_resize(TYPE##_arraylist * list, int capacity)\
    {\
        TYPE* data = realloc_size_type(list->data, capacity, TYPE);\
        if (!data) {\
            perror("Failed to resize data array");\
            return false;\
        }\
        list->data = data;\
        list->capacity = capacity;\
        return true;\
    }\
    bool TYPE##_arraylist_add(TYPE##_arraylist * list, TYPE ele)\
    {                                       \
        if(list->size >= list->capacity)\
        {\
            if(!TYPE##_arraylist_resize(list, list->capacity << 1))\
            {\
                return false;\
            }\
        }\
        list->data[list->size++] = ele;\
        return true;\
    }\
    bool TYPE##_arraylist_insert(TYPE##_arraylist * list, int index, TYPE ele)\
    {\
        if(index > list->size || index < 0)\
        {\
            perror( "Index out of bounds\n");\
            return false;\
        }\
        if(list->size == list->capacity)\
        {\
            if(!TYPE##_arraylist_resize(list, list->capacity << 1))\
            {\
                return false;\
            }\
        }\
        for (int i = list->size; i > index; --i) {\
            list->data[i] = list->data[i-1];\
        }\
        list->data[index] = ele;\
        list->size++;\
        return true;\
    }\
    void TYPE##_arraylist_foreach(TYPE##_arraylist * list, TYPE##_array_foreach func)\
    {\
        for (int i = 0; i < list->size; ++i) {\
            func(list->data[i]);\
        }\
    }\
    void TYPE##_arraylist_destroy(TYPE##_arraylist * list)\
    {\
        free(list->data);\
        free(list);\
    }\
    TYPE TYPE##_arraylist_get(TYPE##_arraylist * list, int index)\
    {\
        return list->data[index];\
    }\
    TYPE TYPE##_arraylist_remove(TYPE##_arraylist * list, int index)          \
    {                                       \
        if (index >= list->size || index < 0)\
        {\
            perror( "Index out of bounds\n");\
            return (TYPE)0;\
        }\
        \
        TYPE removed_ele = list->data[index];\
        \
        for (size_t i = index; i < list->size - 1; ++i)\
        {\
            list->data[i] = list->data[i + 1];\
        }\
        list->size--;\
        if (list->size > 0 && list->size <= (list->capacity >> 2))\
        {\
            TYPE##_arraylist_resize(list, list->capacity >> 1);\
        }\
        return  removed_ele;                                \
    }                                        \
    int TYPE##_arraylist_indexof(TYPE##_arraylist * list, TYPE ele)\
    {\
        for (int i = 0; i < list->size; ++i) {      \
            if(ele == list->data[i])\
            {\
                return i;\
            }\
        }\
        return -1;\
    }

DECLARE_BASE_TYPE_ARRAYLIST(int)
DECLARE_BASE_TYPE_ARRAYLIST(char)
DECLARE_BASE_TYPE_ARRAYLIST(uint32_t)

#endif //ALGORITHM_BASETYPE_ARRAYLIST_H
