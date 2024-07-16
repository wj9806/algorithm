//
// Created by xsy on 2024/7/8.
//

#ifndef ALGORITHM_LINKED_LINKED_QUEUE_H
#define ALGORITHM_LINKED_LINKED_QUEUE_H

#include "linkedlist.h"

typedef struct {
    linkedlist list;
} linked_queue;

/**
 * init a linked_queue
 */
linked_queue * linked_queue_init();

/**
 * init a linked_queue with capacity
 */
linked_queue * linked_queue_init_capacity(int capacity);

/**
 * destroy a linked_queue
 */
void linked_queue_destroy(linked_queue * q);

/**
 * Inserts the specified element into linked_queue
 */
bool linked_queue_offer(linked_queue * q, void * data);

/**
 * Retrieves and removes the head of this linked_queue
 * @return the head of this linked_queue, or (void *)0 if this linked_queue is empty
 */
void * linked_queue_poll(linked_queue * q);

/**
 * Retrieves, but does not remove, the head of this linked_queue,
 * @return the head of this linked_queue, or (void *)0 if this linked_queue is empty
 */
void * linked_queue_peek(linked_queue * q);

/**
 * Returns linked_queue size
 */
static inline int linked_queue_size(linked_queue * q)
{
    return linkedlist_size(&q->list);
}

/**
 * Returns true if this linked_queue contains no elements.
 */
static inline bool linked_queue_is_empty(linked_queue * q)
{
    return linked_queue_size(q) == 0;
}

/**
 * Returns true if this linked_queue contains the specified element.
 */
bool linked_queue_contains(linked_queue * q, void * data);

/**
 * Returns linked_queue capacity
 */
static inline int linked_queue_capacity(linked_queue * q)
{
    return q->list.capacity;
}

#endif //ALGORITHM_LINKED_linked_queue_H
