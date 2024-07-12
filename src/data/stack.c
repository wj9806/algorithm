//
// Created by xsy on 2024/7/8.
//

#include "stack.h"

stack * stack_init()
{
    return stack_init_capacity(INT_MAX);
}

stack * stack_init_capacity(int capacity)
{
    stack * s = (stack *)malloc(sizeof(stack));
    if(!s)
    {
        debug_error("Failed to create stack");
        return (stack *) 0;
    }

    s->list.first = s->list.last = (node *)0;
    s->list.size = 0;
    s->list.capacity = capacity;
    return s;
}

void stack_destroy(stack * q)
{
    linkedlist list = q->list;
    node * n;
    linkedlist_for_each(n, &list)
    {
        free(n);
    }
    free(q);
}

bool stack_push(stack * q, void * data)
{
    return linkedlist_insert_first(&q->list, data);
}

void * stack_pop(stack * q)
{
    return linkedlist_remove_first(&q->list);
}

void * stack_peek(stack * q)
{
    return linkedlist_first(&q->list);
}

bool stack_contains(stack * s, void * data)
{
    return linkedlist_contains(&s->list, data);
}