//
// Created by xsy on 2024/7/8.
//

#include "queue.h"
#include <stdlib.h>

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
    q->list.capacity = INT_MAX;
    return q;
}

queue * queue_init_capacity(int capacity)
{
    queue * q = queue_init();
    q->list.capacity = capacity;
    return q;
}

void queue_destroy(queue * q)
{
    linkedlist list = q->list;
    node * n;
    linkedlist_for_each(n, &list)
    {
        free(n);
    }
    free(q);
}

bool queue_offer(queue * q, void * data)
{
    return linkedlist_insert_last(&q->list, data);
}

void * queue_poll(queue * q)
{
    return linkedlist_remove_first(&q->list);
}

void * queue_peek(queue * q)
{
    return linkedlist_first(&q->list)->data;
}

bool queue_contains(queue * q, void * data)
{
    return linkedlist_contains(&q->list, data);
}