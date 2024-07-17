//
// Created by xsy on 2024/7/11.
//
#include "tree_map.h"
#include "tree_set.h"
#include <stdio.h>

#define put(i) \
     printf("insert: %d\n", i);             \
     int in##i = i;     \
     tree_map_put(map, &in##i, &in##i);  \
     tree_map_print(map, printf_int_node);

#define add(i) \
     printf("add: %d\n", i);             \
     int in##i = i;     \
     tree_set_add(set, &in##i);

#define remove(i) \
    printf("remove: %d, ", i); \
    printf("return:%d\n", *(int*)tree_map_remove(map, &in##i));\
    tree_map_print(map, printf_int_node);

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
    put(1)
    put(2)
    put(3)
    put(4)
    put(5)
    put(6)
    put(7)
    put(8)
    put(9)

    remove(4)

    printf("%d\n", *(int*)tree_map_get(map, &in1));

    printf("---------------------IN-------------------\n");
    tree_map_foreach(map, printk, IN);

    tree_map_destroy(map, true, true);
}

void tree_set_test()
{
    tree_set *set= tree_set_init(int_compare);
    add(1)
    add(2)

    int * data;
    tree_set_foreach(set, data)
    {
        printf("%p\n", node);
        printf("%d\n", *data);
    }

    tree_set_destroy(set, false);

    printf("111111\n");
}

void tree_map_test()
{
#ifdef TEST_TREE_MAP
    tree_map_put_test();
    tree_set_test();
#endif
}

