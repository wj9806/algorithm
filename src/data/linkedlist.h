//
// Created by wj on 2024/7/3.
//

#ifndef ALGORITHM_LINKEDLIST_H
#define ALGORITHM_LINKEDLIST_H

#include "common.h"
#include <limits.h>

typedef struct node {
    /** pre node */
    struct node * pre;
    /** next node */
    struct node * next;
    /* data */
    void * data;
} node;

/**
 * Returns node's pre node
 */
static inline node * linkedlist_node_pre(node * node)
{
    return node->pre;
}

/**
 * Returns node's next node
 */
static inline node * linkedlist_node_next(node * node)
{
    return node->next;
}

typedef struct linkedlist {
    /** the first node of linkedlist*/
    node * first;
    /** the last node of linkedlist*/
    node * last;
    /** the size of linkedlist*/
    int size;
    /** the capacity of linkedlist**/
    int capacity;
} linkedlist;

/**
 * init linkedlist
 */
linkedlist * linkedlist_init();

/**
 * init linkedlist with capacity
 */
linkedlist * linkedlist_init_capacity(int capacity);

/**
 * destroy linkedlist
 */
void linkedlist_destroy(linkedlist * list);

/**
 * Returns true if this list contains no elements.
 */
static inline int linkedlist_is_empty(linkedlist * list)
{
    return list->size == 0;
}

/**
 * Returns list size
 */
static inline int linkedlist_size(linkedlist * list)
{
    return list->size;
}

/**
 * Returns the first node in this list.
 */
static inline node * linkedlist_first(linkedlist * list)
{
    return list->first;
}

/**
 * Returns the last node in this list.
 */
static inline node * linkedlist_last(linkedlist * list)
{
    return list->last;
}

/**
 * Set next node
 */
static inline void linkedlist_node_set_next(node* pre, node* next) {
    pre->next = next;
    next->pre = pre;
}

/**
 * Returns linkedlist capacity
 */
static inline int linkedlist_capacity(linkedlist * list)
{
    return list->capacity;
}

/**
 * Inserts the specified node at the beginning of this list.
 */
bool linkedlist_insert_first(linkedlist * list, void * data);

/**
 * Appends the specified node to the end of this list.
 */
bool linkedlist_insert_last(linkedlist * list, void * data);

#define linkedlist_add(list, data) linkedlist_insert_last(list, data)

/**
 * Removes and returns the first node from this list.
 */
void * linkedlist_remove_first(linkedlist * list);

/**
 * Removes and returns the last node from this list.
 */
void * linkedlist_remove_last(linkedlist * list);

/**
 * Removes and returns the given node
 */
bool linkedlist_remove(linkedlist * list, void * data);

/**
 * Inserts a node after a given node
 * @param list list
 * @param pre given node
 * @param node The node that needs to be Insert in
 */
bool linkedlist_insert_after(linkedlist * list, void * pre_data, void * cur_data);

/**
 * Returns true if this list contains the specified element.
 */
bool linkedlist_contains(linkedlist * list, void * data);

#define linkedlist_for_each(node, list)      for ((node) = (list)->first; (node); (node) = (node)->next)


#endif //ALGORITHM_LINKEDLIST_H
