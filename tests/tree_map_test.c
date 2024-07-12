//
// Created by xsy on 2024/7/11.
//
#include "tree_map.h"
#include <stdio.h>

#define put(m, i) \
     int in##i = i;     \
     tree_map_put(m, &in##i, &in##i);

int int_compare(void * k1, void * k2)
{
    return *(int*)k1 - *(int*)k2;
}

void printk(void * k, void * v)
{
    printf("{%d - %d}\n", *(int*)k, *(int*)v);
}

void tree_map_put_test()
{
    tree_map * map = tree_map_init(int_compare);
    put(map, 1);
    put(map, 2);
    put(map, 3);
    put(map, 4);
    put(map, 5);
    put(map, 6);
    put(map, 7);
    put(map, 8);

    printf("---------------------PRE-------------------\n");
    tree_map_foreach(map, printk, PRE);
    printf("----------------------IN------------------\n");
    tree_map_foreach(map, printk, IN);
    printf("---------------------POST-------------------\n");
    tree_map_foreach(map, printk, POST);
    printf("---------------------LEVEL-------------------\n");
    tree_map_foreach(map, printk, LEVEL);
}

void tree_map_test()
{
#ifdef TEST_TREE_MAP
    tree_map_put_test();
#endif
}

