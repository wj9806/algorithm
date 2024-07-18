//
// Created by xsy on 2024/7/17.
//

#ifndef ALGORITHM_B_TREE_H
#define ALGORITHM_B_TREE_H

#include "common.h"

/* b_tree element */
typedef struct {
    void * key;
    void * value;
} b_entry;

typedef struct b_node{
    /* entries in the node */
    b_entry ** entries;
    /* node's children */
    struct b_node ** children;
    /* keywords number */
    int key_number;
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
} b_tree;

/**
 * create a b-tree
 * @param t The minimum degree of the tree
 * @param compare key compare function
 * @return
 */
b_tree * btree_init(int t, compare compare);

/**
 * Returns true if this b-tree contains the specified element.
 */
bool b_tree_contains_key(b_tree * tree, void * key);

/* put key */
void * b_tree_put(b_tree * tree, void * key, void * value);

#endif //ALGORITHM_B_TREE_H
