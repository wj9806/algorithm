//
// Created by xsy on 2024/7/8.
//

#ifndef ALGORITHM_STACK_H
#define ALGORITHM_STACK_H

#include "linkedlist.h"

typedef struct {
    linkedlist list;
} stack;

/**
 * init a stack
 */
stack * stack_init();

/**
 * init a stack with capacity
 */
stack * stack_init_capacity(int capacity);

/**
 * destroy a stack
 */
void stack_destroy(stack * s);

/**
 * Pushes an item onto the top of this stack
 */
bool stack_push(stack * s, void * data);

/**
 * Removes the object at the top of this stack
 * @return the top of this stack, or (void *)0 if this stack is empty
 */
void * stack_pop(stack * s);

/**
 * Retrieves, but does not remove, the top of this stack,
 * @return the top of this stack, or (void *)0 if this stack is empty
 */
void * stack_peek(stack * s);

/**
 * Returns stack size
 */
static inline int stack_size(stack * s)
{
    return linkedlist_size(&s->list);
}

/**
 * Returns true if this stack contains no elements.
 */
static inline bool stack_is_empty(stack * s)
{
    return stack_size(s) == 0;
}

/**
 * Returns true if this stack contains the specified element.
 */
bool stack_contains(stack * s, void * data);

/**
 * Returns stack capacity
 */
static inline int stack_capacity(stack * s)
{
    return s->list.capacity;
}

#endif //ALGORITHM_STACK_H
