//
// Created by xsy on 2024/7/17.
//

#ifndef ALGORITHM_B_TREE_H
#define ALGORITHM_B_TREE_H

#include "common.h"
#include "function.h"

/* b_tree element */
typedef struct {
    void * key;
    void * value;
} b_entry;

typedef struct b_node{
    /* keywords number */
    int key_number;
    /* entries in the node */
    b_entry ** entries;
    /* node's children */
    struct b_node ** children;
    /* is leaf */
    bool leaf;
    /* The minimum degree of the tree */
    int t;
    /* key compare function */
    compare compare;
} b_node;

typedef struct {
    /* tree root */
    b_node * root;
    /* tree size */
    int size;
    /* key compare function */
    compare compare;
    /* The minimum degree of the tree */
    int t;
    /* min key count */
    int min_key_count;
    /* max key count */
    int max_key_count;
    /* key free function */
    free_func key_free;
    /* value free function */
    free_func value_free;
} b_tree;

/**
 * create a b-tree
 * @param t The minimum degree of the tree
 * @param compare key compare function
 * @return
 */
b_tree * btree_init(int t, compare compare, free_func key_free, free_func value_free);

/**
 * Returns true if this b-tree contains the specified element.
 */
bool b_tree_contains_key(b_tree * tree, void * key);

/* put key */
void * b_tree_put(b_tree * tree, void * key, void * value);

/* remove key */
void * b_tree_remove(b_tree * tree, void * key);

/* Returns the value to which the specified key is mapped,
   or null if this map contains no mapping for the key. */
void * b_tree_get(b_tree * tree, void * key);

/* clear b-tree */
void b_tree_clear(b_tree * tree);

/* destroy b-tree */
void b_tree_destroy(b_tree * tree);

/* Returns the b-tree depth */
int b_tree_depth(b_tree * m);

/* Returns b-tree size */
static inline int b_tree_size(b_tree * tree)
{
    return tree->size;
}

/* Returns the b-tree is empty */
static inline bool b_tree_is_empty(b_tree * tree)
{
    return tree->size == 0;
}

/**
 * Performs the given action for each entry in this tree until all entries have been processed
 * @param preorder traversal, inorder traversal, postorder traversal, level order traversal
 */
void b_tree_foreach(b_tree * m, bi_consumer consumer, traversal tra);

#ifdef  TEST_B_TREE
void printf_b_node(b_node * node);
#else
#define printf_node(n)
#endif

#endif //ALGORITHM_B_TREE_H
