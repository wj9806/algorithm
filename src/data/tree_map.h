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

typedef struct {
    tree_node * root;
    unsigned int size;
    compare compare;
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

/* destroy tree map */
void tree_map_destroy(tree_map * m, bool free_key, bool free_value);

/* init tree map*/
tree_map * tree_map_init(compare compare);

/* put k v*/
void * tree_map_put(tree_map * m, void * k, void * v);

/* Removes the mapping for this key from this TreeMap if present. */
void * tree_map_remove(tree_map * m, void * k);

/* Removes all of the mappings from this map. */
void tree_map_clear(tree_map * m, bool free_key, bool free_value);

/* Returns the value to which the specified key is mapped,
   or null if this map contains no mapping for the key. */
void * tree_map_get(tree_map * m, void * k);

/* Returns true if this tree map contains a mapping for the specified key. */
bool tree_map_contains_key(tree_map * m, void * k);

//-------------------------------- foreach ------------------------------//

/* Returns the first (lowest) key currently in this map. */
void * tree_map_first_key(tree_map * m);

/* Returns the last (highest) key currently in this map. */
void * tree_map_last_key(tree_map * m);

/* Returns the first (lowest) node currently in this map. */
tree_node * tree_map_first_node(tree_map * m);

/* Returns the last (highest) node currently in this map. */
tree_node * tree_map_last_node(tree_map * m);

/**
 * Returns the predecessor of the specified tree node
 */
tree_node * tree_node_predecessor(tree_node * n);

/**
 * Returns the successor of the specified tree node
 */
tree_node * tree_node_successor(tree_node * n);

typedef enum {
    PRE, IN, POST, LEVEL
} traversal;

/**
 * Performs the given action for each entry in this map until all entries have been processed
 * @param preorder traversal, inorder traversal, postorder traversal, level order traversal
 */
void tree_map_foreach(tree_map * m, bi_consumer consumer, traversal tra);

/**
 * Return to the height of the red and black trees
 */
int tree_map_depth(tree_map * m);

//-----------------------debug-------------------------

/**
 * printf_tree_node function
 */
typedef void (*printf_tree_node)(tree_node * node);

/* printf tree map */
void tree_map_print(tree_map *map, printf_tree_node func);

#endif //ALGORITHM_TREE_MAP_H
