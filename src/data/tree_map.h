//
// Created by xsy on 2024/7/11.
//

#ifndef ALGORITHM_TREE_MAP_H
#define ALGORITHM_TREE_MAP_H

#include "common.h"
#include "function.h"
#include "linkedlist.h"

//red bg
#define RED_BG      "\033[41m"
//grep bg
#define GRAY_BG     "\033[100m"
//white font
#define WHITE_FG    "\033[97m"
//reset color
#define RESET       "\033[0m"

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

typedef enum {
    PRE, IN, POST, LEVEL
} traversal;

/**
 * Performs the given action for each entry in this map until all entries have been processed
 * @param preorder traversal, inorder traversal, postorder traversal, level order traversal
 */
void tree_map_foreach(tree_map * m, bi_consumer consumer, traversal tra);

struct node_ele
{
    int index;
    tree_node * node;
};

/**
 * Return to the height of the red and black trees
 */
int tree_map_depth(tree_map * m);

/* get a list view of the tree node in this map. */
void node_list(tree_map * m, linkedlist * list, int * tree_depth, int * full_size);

/**
 * printf_tree_node function
 */
typedef void (*printf_tree_node)(tree_node * node);

/* printf tree map */
void tree_map_print(tree_map *map, printf_tree_node func);

#endif //ALGORITHM_TREE_MAP_H
