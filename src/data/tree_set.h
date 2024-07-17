//
// Created by xsy on 2024/7/16.
//

#ifndef ALGORITHM_TREE_SET_H
#define ALGORITHM_TREE_SET_H

#include "tree_map.h"

typedef struct {
    tree_map * m;
} tree_set;

/**
 * init tree_set
 * @param compare tree_map's key comparator
 * @return
 */
tree_set * tree_set_init(key_compare compare);

/**
 * Adds the specified element to this set if it is not already present.
 * @return true if this set did not already contain the specified
 */
bool tree_set_add(tree_set * set, void * value);

/**
 * Removes the specified element from this set if it is present.
 * true if the set contained the specified element
 */
bool tree_set_remove(tree_set * set, void * value);

/* Returns the first (lowest) element currently in this set. */
void * tree_set_first(tree_set * set);

/* Returns the last (highest) element currently in this set. */
void * tree_set_last(tree_set * set);

/**
 * Removes all of the elements from this set.
 * The set will be empty after this call returns.
 * @param value should free value ?
 */
void tree_set_clear(tree_set * set, bool value);

/**
 * destroy the tree_set
 * @param value should free value ?
 */
void tree_set_destroy(tree_set * set, bool value);

/**
 * Returns {@code true} if this set contains the specified element.
 */
bool tree_set_contains(tree_set * set, void * value);

/* Returns hash set size */
static inline unsigned int tree_set_size(tree_set * set)
{
    return set->m->size;
}

/* Returns true if this hash set is empty */
static inline bool tree_set_is_empty(tree_set * set)
{
    return !set || set->m->size == 0;
}

#define tree_set_foreach(set, data) \
    tree_node *node = tree_map_first_node((set)->m);\
    for ((data) = node->key; node; node = tree_node_successor(node), (data) = node ? node->key : (data))

#endif //ALGORITHM_TREE_SET_H
