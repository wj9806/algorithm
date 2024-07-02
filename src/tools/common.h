//
// Created by wj on 2024/7/2.
//

#ifndef ALGORITHM_COMMON_H
#define ALGORITHM_COMMON_H

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


#endif //ALGORITHM_COMMON_H
