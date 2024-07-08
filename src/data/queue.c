//
// Created by xsy on 2024/7/8.
//

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

queue * queue_init()
{
    queue * q = (queue *)malloc(sizeof(queue));
    if(!q)
    {
        debug_error("Failed to create queue");
        return (queue *) 0;
    }

    q->list.first = q->list.last = (node *)0;
    q->list.size = 0;
    return q;
}

void queue_destroy(queue * q)
{
    free(q);
}