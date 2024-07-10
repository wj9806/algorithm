//
// Created by xsy on 2024/7/10.
//

#ifndef ALGORITHM_FUNCTION_H
#define ALGORITHM_FUNCTION_H

typedef void * (*function)(void * t);
typedef void (*consumer)(void * t);
typedef void (*bi_consumer)(void * t, void * v);

#endif //ALGORITHM_FUNCTION_H
