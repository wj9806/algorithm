//
// Created by xsy on 2024/7/18.
//
#include "b_tree.h"
#include <stdio.h>

#define b_put(i) \
    printf("put %d--------------------\n", i);    \
    int t##i = i;\
    b_tree_put(tree, &t##i, &t##i); \
    printf_b_node(tree->root);                      \
    printf("depth: %d\n", b_tree_depth(tree));

void b_tree_node_testing()
{
    b_tree_node_test();
}

void b_tree_put_testing()
{
    printf("b_tree_put_testing.........\n");
    int t = 2;
    b_tree * tree = btree_init(t, int_compare, 0, 0);
    b_put(1)
    b_put(2)
    b_put(3)
    b_put(4)
    b_put(5)
    b_put(6)
    b_put(7)
    b_put(8)
    b_put(9)
    b_put(10)
    b_put(11)
}

void b_tree_test()
{
#ifdef  TEST_B_TREE
    b_tree_node_testing();
    b_tree_put_testing();
#endif
}