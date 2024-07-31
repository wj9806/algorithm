//
// Created by wj on 2024/7/2.
//

#ifndef ALGORITHM_COMMON_H
#define ALGORITHM_COMMON_H

#include <stdlib.h>
#include <stdbool.h>

#define ELE void*

#define malloc_type(TYPE) \
    (TYPE*)malloc(sizeof(TYPE))

#define malloc_size_type(SIZE, TYPE) \
    (TYPE*)malloc((SIZE) * sizeof(TYPE))

#define calloc_size_type(SIZE, TYPE) \
    (TYPE*)calloc((SIZE), sizeof(TYPE))

#define realloc_type(BLOCK, TYPE) \
    (TYPE*)realloc(BLOCK, sizeof(TYPE))

#define realloc_size_type(BLOCK, SIZE, TYPE) \
    (TYPE*)realloc(BLOCK, (SIZE) * sizeof(TYPE))

#define DEBUG_STYLE_RED         "\033[31m"
#define DEBUG_STYLE_YELLOW      "\033[33m"
#define DEBUG_STYLE_WHITE       "\033[0m"

#define DEBUG_LEVEL_NONE        0
#define DEBUG_LEVEL_ERROR       1
#define DEBUG_LEVEL_WARN        2
#define DEBUG_LEVEL_INFO        3

void debug_print(int level, const char * file, const char * func, int line, const char * fmt, ...);

#define debug_info(fmt, ...)  debug_print(DEBUG_LEVEL_INFO, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define debug_warn(fmt, ...)  debug_print(DEBUG_LEVEL_WARN, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define debug_error(fmt, ...) debug_print(DEBUG_LEVEL_ERROR, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#define assert(expr, msg) { \
    if(!(expr))             \
    {                       \
        debug_print(DEBUG_LEVEL_ERROR, __FILE__, __FUNCTION__, __LINE__, "assert failed: "#expr", "msg);       \
        exit(1);           \
    }                       \
}

/**
 * tree traversal:
 *  preorder traversal, inorder traversal, postorder traversal, level order traversal
 */
typedef enum {
    PRE, IN, POST, LEVEL
} traversal;


/**
 * Returns a negative integer, zero, or a positive integer as k1 is less
 * than, equal to, or greater than the k2.
 */
typedef int (*compare)(void * k1, void * k2);

/**
 * Sort function
 */
typedef void (*sort_func)(void* data[], int arr_len, compare cp, bool nature_sort);

/* compare int */
int int_compare(void * k1, void * k2);

/* hash code function */
typedef long (*hash_code)(void * key);

/* compute the int hash code */
long int_hash_code(void * key);

/* compute the ptr hash code */
long void_hash_code(void * key);

/* free mem function */
typedef void (*free_func)(void * ptr);

/* call free function */
void default_free_func(void * ptr);

#endif //ALGORITHM_COMMON_H
