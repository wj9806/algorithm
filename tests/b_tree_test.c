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

#define b_remove(i) \
    printf("remove---%d\n", *(int*)b_tree_remove(tree, &t##i)); \
    printf_b_node(tree->root);

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

    printf("t1=%d\n", *(int*)b_tree_get(tree, &t1));
    printf("t2=%d\n", *(int*)b_tree_get(tree, &t2));
    printf("t3=%d\n", *(int*)b_tree_get(tree, &t3));
    printf("t4=%d\n", *(int*)b_tree_get(tree, &t4));
    printf("t5=%d\n", *(int*)b_tree_get(tree, &t5));
    printf("t6=%d\n", *(int*)b_tree_get(tree, &t6));

    b_tree_destroy(tree);
}

void b_tree_remove_testing()
{
    printf("b_tree_remove_testing.........\n");
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

    printf("~~~~~~~~~~%d~~~~~~~~~~~~\n", b_tree_size(tree));

    b_remove(11)
    b_remove(10)
    b_remove(9)
    b_remove(8)
    b_remove(7)
    b_remove(6)
    b_remove(5)
    b_remove(4)
    b_remove(3)
    b_remove(2)
    b_remove(1)
    printf("~~~~~~~~~~%d~~~~~~~~~~~~\n", b_tree_size(tree));

    b_put(12)
    b_put(22)
    b_put(13)
    printf("~~~~~~~~~~%d~~~~~~~~~~~~\n", b_tree_size(tree));

    b_tree_destroy(tree);
}

void b_tree_test()
{
#ifdef  TEST_B_TREE
    b_tree_put_testing();
    b_tree_remove_testing();
#endif
}