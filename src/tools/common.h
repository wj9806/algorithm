//
// Created by wj on 2024/7/2.
//

#ifndef ALGORITHM_COMMON_H
#define ALGORITHM_COMMON_H

#include <stdlib.h>

#define true        1
#define false       0
#define bool        int

#define malloc_type(TYPE) \
    (TYPE*)malloc(sizeof(TYPE))

#define malloc_size_type(SIZE, TYPE) \
    (TYPE*)malloc(SIZE * sizeof(TYPE))

#define realloc_type(BLOCK, TYPE) \
    (TYPE*)realloc(BLOCK, sizeof(TYPE))

#define realloc_size_type(BLOCK, SIZE, TYPE) \
    (TYPE*)realloc(BLOCK, SIZE * sizeof(TYPE))

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


#endif //ALGORITHM_COMMON_H
