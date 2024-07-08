//
// Created by xsy on 2024/7/8.
//

#ifndef ALGORITHM_QUEUE_H
#define ALGORITHM_QUEUE_H

#include "linkedlist.h"

typedef struct {
    linkedlist list;
} queue;

/**
 * init a queue
 */
queue * queue_init();

/**
 * init a queue with capacity
 */
queue * queue_init_capacity(int capacity);

/**
 * destroy a queue
 */
void queue_destroy(queue * q);

/**
 * Inserts the specified element into queue
 */
bool queue_offer(queue * q, void * data);

/**
 * Retrieves and removes the head of this queue
 * @return the head of this queue, or (void *)0 if this queue is empty
 */
void * queue_poll(queue * q);

/**
 * Retrieves, but does not remove, the head of this queue,
 * @return the head of this queue, or (void *)0 if this queue is empty
 */
void * queue_peek(queue * q);

/**
 * Returns queue size
 */
static inline int queue_size(queue * q)
{
    return linkedlist_size(&q->list);
}

/**
 * Returns true if this queue contains no elements.
 */
static inline bool queue_is_empty(queue * q)
{
    return queue_size(q) == 0;
}

/**
 * Returns true if this queue contains the specified element.
 */
bool queue_contains(queue * q, void * data);

/**
 * Returns queue capacity
 */
static inline int queue_capacity(queue * q)
{
    return q->list.capacity;
}

#endif //ALGORITHM_QUEUE_H
