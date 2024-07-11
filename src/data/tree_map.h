//
// Created by xsy on 2024/7/11.
//

#ifndef ALGORITHM_TREE_MAP_H
#define ALGORITHM_TREE_MAP_H

#include "common.h"

/* the tree node of color */
typedef enum {
    RED,BLACK
} color;

/* the tree of node */
typedef struct tree_node {
    struct tree_node * parent;
    struct tree_node * left;
    struct tree_node * right;
    color color;
    void * key;
    void * value;
} tree_node;

/**
 * Returns a negative integer, zero, or a positive integer as k1 is less
 * than, equal to, or greater than the k2.
 */
typedef int (*key_compare)(void * k1, void * k2);

typedef struct {
    tree_node * root;
    unsigned int size;
    key_compare compare;
} tree_map;

/* Returns the tree map size */
static inline unsigned int tree_map_size(tree_map * m)
{
    return m->size;
}

/* Returns the tree map is empty */
static inline bool tree_map_is_empty(tree_map * m)
{
    return !m || m->size == 0;
}

/* create tree node */
tree_node * tree_node_create(tree_node * parent, tree_node * left, tree_node * right,
                             color color, void * key, void * value);

/* init tree map*/
tree_map * tree_map_init(key_compare compare);

/* put k v*/
void * tree_map_put(tree_map * m, void * k, void * v);

#endif //ALGORITHM_TREE_MAP_H
