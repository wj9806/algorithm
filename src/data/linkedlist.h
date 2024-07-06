//
// Created by wj on 2024/7/3.
//

#ifndef ALGORITHM_LINKEDLIST_H
#define ALGORITHM_LINKEDLIST_H

typedef struct node {
    /** pre node */
    struct node * pre;
    /** next node */
    struct node * next;
} node;

/** init node */
static inline void node_init(node * n)
{
    n->pre = n->next = (node*)0;
}

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
} linkedlist;

/**
 * init linkedlist
 */
linkedlist * linkedlist_init();

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
 * Inserts the specified node at the beginning of this list.
 */
void linkedlist_insert_first(linkedlist * list, node * node);

/**
 * Appends the specified node to the end of this list.
 */
void linkedlist_insert_last(linkedlist * list, node * node);

/**
 * Removes and returns the first node from this list.
 */
node * linkedlist_remove_first(linkedlist * list);

/**
 * Removes and returns the last node from this list.
 */
node * linkedlist_remove_last(linkedlist * list);

/**
 * Removes and returns the given node
 */
node * linkedlist_remove(linkedlist * list, node * node);

/**
 * Inserts a node after a given node
 * @param list list
 * @param pre given node
 * @param node The node that needs to be Insert in
 */
void linkedlist_insert_after(linkedlist * list, node * pre, node * node);

//Gets the relative address offset of the node_name in the parent_type
#define offset_int_parent(parent_type, node_name) \
    ((char *)&(((parent_type *)0)->node_name))

//Get the address of the parent_type
#define parent_addr(node, parent_type, node_name) \
    ((char *)node - offset_int_parent(parent_type, node_name))

//Convert to parent_type* struct
#define linkedlist_node_parent(node, parent_type, node_name) \
    ((parent_type *)(node ? parent_addr(node, parent_type, node_name) : 0))

#define linkedlist_for_each(node, list)      for ((node) = (list)->first; (node); (node) = (node)->next)

#endif //ALGORITHM_LINKEDLIST_H
