//
// Created by xsy on 2024/7/8.
//

#ifndef ALGORITHM_QUEUE_H
#define ALGORITHM_QUEUE_H

#include "linkedlist.h"

typedef struct {
    linkedlist list;
} queue;

queue * queue_init();

void queue_destroy();

#endif //ALGORITHM_QUEUE_H
