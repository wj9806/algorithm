//
// Created by xsy on 2024/7/11.
//
#include "tree_map.h"
#include <stdio.h>

#define put(m, i) \
     printf("insert: %d\n", i);             \
     int in##i = i;     \
     tree_map_put(m, &in##i, &in##i);  \
     tree_map_print(map, printf_int_node);

static int int_compare(void * k1, void * k2)
{
    return *(int*)k1 - *(int*)k2;
}

static void printf_int_node(tree_node * node)
{
    if(node)
    {
        if(node->color == RED)
        {
            printf(RED_BG WHITE_FG "%2d" RESET, *(int*)node->key);
        }
        else
        {
            printf(GRAY_BG WHITE_FG "%2d" RESET, *(int*)node->key);
        }
    }
    else
    {
        printf("  ");
    }
}

static void printk(void * k, void * v)
{
    printf("{%d - %d}\n", *(int*)k, *(int*)v);
}


void tree_map_put_test() {
    tree_map *map = tree_map_init(int_compare);
    put(map, 11);
    put(map, 12);
    put(map, 13);
    put(map, 14);
    put(map, 15);
    put(map, 16);
    put(map, 17);
    put(map, 18);

    printf("---------------------LEVEL-------------------\n");
    tree_map_foreach(map, printk, LEVEL);
}

void tree_map_test()
{
#ifdef TEST_TREE_MAP
    tree_map_put_test();
#endif
}

