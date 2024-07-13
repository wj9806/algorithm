//
// Created by xsy on 2024/7/11.
//
#include "tree_map.h"
#include <stdio.h>
#include "queue.h"
#include "linkedlist.h"

//red bg
#define RED_BG      "\033[41m"
//grep bg
#define GRAY_BG     "\033[100m"
//white font
#define WHITE_FG    "\033[97m"
//reset color
#define RESET       "\033[0m"

#define put(m, i) \
     printf("insert: %d\n", i);             \
     int in##i = i;     \
     tree_map_put(m, &in##i, &in##i);  \
     printf_rd_tree(map);

static int int_compare(void * k1, void * k2)
{
    return *(int*)k1 - *(int*)k2;
}

static void printk(void * k, void * v)
{
    printf("{%d - %d}\n", *(int*)k, *(int*)v);
}

static void printf_node(tree_node * node)
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

struct print_node
{
    int index;
    tree_node * node;
};

/* Returns the size of full binary tree */
int full_tree_size(int depth)
{
    return depth ? (2 << depth) - 1 : 0;
}

static void key_list(tree_map * m, linkedlist * list, int * tree_depth, int * full_size)
{
    *tree_depth = tree_map_depth(m);
    *full_size = full_tree_size(*tree_depth);
    int size = *full_size;

    queue* q = queue_init();
    queue_offer(q, m->root);
    while (queue_size(q) > 0 && size--)
    {
        tree_node * n = queue_poll(q);

        if (n)
        {
            struct print_node * pn = malloc_type(struct print_node);
            pn->node = n;
            pn->index = *full_size - size - 1;
            linkedlist_add(list, pn);
        }

        queue_offer(q, n ? n->left : 0);
        queue_offer(q, n ? n->right : 0);
    }
    queue_destroy(q);
}

void print_spaces(int count) {
    for (int i = 0; i < count; i++) {
        printf("  ");
    }
}

void printf_rd_tree(tree_map *map) {
    int full_size;
    int depth;
    linkedlist * list = linkedlist_init();
    key_list(map, list, &depth, &full_size);

    for (int i = depth, level = 0, all = 0; i > 0; --i, level++) {
        int count = level ? 2 << (level - 1) : 1;
        for (int j = 0; j < count; j++)
        {
            if (j)
                print_spaces((2 << (depth - level)) -1);
            else
                print_spaces((2 << (depth - level - 1)));

            if (((struct print_node *) linkedlist_first(list))->index == all++)
                printf_node(((struct print_node *)linkedlist_remove_first(list))->node);
            else
                printf_node((tree_node*)0);
        }
        printf("\n");
    }

    node * n, * head = list->first;
    while (head)
    {
        n = head->next;
        free(head->data);
        free(head);
        head = n;
    }
    free(list);
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

