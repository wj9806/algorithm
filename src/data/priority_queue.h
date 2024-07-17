//
// Created by xsy on 2024/7/16.
//

#ifndef ALGORITHM_PRIORITY_QUEUE_H
#define ALGORITHM_PRIORITY_QUEUE_H

#include <stdbool.h>

#define E void*

/* the priority queue elements priority */
typedef int (*priority_comparator)(E e1, E e2);

typedef struct {
    /** the arraylist capacity */
    int capacity;
    /** the arraylist size */
    int size;
    /** data array */
    E * data;
    /* priority queue elements comparator */
    priority_comparator comparator;
} priority_queue;

/* init priority_queue */
priority_queue * priority_queue_init(int capacity, priority_comparator comparator);

/**
 * destroy the given priority_queue
 * @param free_ele free priority_queue's elements
 */
void priority_queue_destroy(priority_queue * q, bool free_ele);

/**
 * Inserts the specified element into priority_queue
 */
bool priority_queue_offer(priority_queue * q, E data);

/**
 * Retrieves and removes the head of this priority_queue
 * @return the head of this priority_queue, or (void *)0 if this priority_queue is empty
 */
E priority_queue_poll(priority_queue * q);

/**
 * Retrieves, but does not remove, the head of this priority_queue,
 * @return the head of this priority_queue, or (void *)0 if this priority_queue is empty
 */
E priority_queue_peek(priority_queue * q);

/* Removes all of the elements from this priority queue. */
void priority_queue_clear(priority_queue * q, bool free_ele);

/**
 * Returns priority_queue size
 */
static inline int priority_queue_size(priority_queue * q)
{
    return q->size;
}

/**
 * Returns true if this priority_queue contains no elements.
 */
static inline bool priority_queue_is_empty(priority_queue * q)
{
    return priority_queue_size(q) == 0;
}

#define priority_queue_foreach(q, e) \
         e = (q)->data[0]; \
         for(int i = 0; i < (q)->size; i++, (e) = (q)->data[i])

#endif //ALGORITHM_PRIORITY_QUEUE_H
