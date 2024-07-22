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

/* clear b-tree */
void b_tree_clear(b_tree * tree);

/* destroy b-tree */
void b_tree_destroy(b_tree * tree);

int b_tree_depth(b_tree * m);

#ifdef  TEST_B_TREE
void b_tree_node_test();
void printf_b_node(b_node * node);
#else
#define b_tree_node_test()
#define printf_node(n)
#endif

#endif //ALGORITHM_B_TREE_H
