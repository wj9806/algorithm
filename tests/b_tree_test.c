//
// Created by xsy on 2024/7/18.
//
#include "b_tree.h"

void b_tree_node_testing()
{
    b_tree_node_test();
}

void b_tree_test()
{
#ifdef  TEST_B_TREE
    b_tree_node_testing();
#endif
}