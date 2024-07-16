//
// Created by xsy on 2024/7/8.
//

#include "linked_queue.h"
#include <stdlib.h>

linked_queue * linked_queue_init()
{
    return linked_queue_init_capacity(INT_MAX);
}

linked_queue * linked_queue_init_capacity(int capacity)
{
    linked_queue * q = (linked_queue *)malloc(sizeof(linked_queue));
    if(!q)
    {
        debug_error("Failed to create linked_queue");
        return (linked_queue *) 0;
    }

    q->list.first = q->list.last = (node *)0;
    q->list.size = 0;
    q->list.capacity = capacity;
    return q;
}

void linked_queue_destroy(linked_queue * q)
{
    linkedlist list = q->list;
    node * n, * head = list.first;
    while (head)
    {
        n = head->next;
        free(head);
        head = n;
    }
    free(q);
}

bool linked_queue_offer(linked_queue * q, void * data)
{
    return linkedlist_insert_last(&q->list, data);
}

void * linked_queue_poll(linked_queue * q)
{
    return linkedlist_remove_first(&q->list);
}

void * linked_queue_peek(linked_queue * q)
{
    return linkedlist_first(&q->list);
}

bool linked_queue_contains(linked_queue * q, void * data)
{
    return linkedlist_contains(&q->list, data);
}