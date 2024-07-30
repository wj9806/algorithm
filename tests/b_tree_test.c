//
// Created by xsy on 2024/7/18.
//
#include "b_tree.h"
#include "linked_queue.h"
#include <stdio.h>

#ifdef  TEST_B_TREE

/* used in b-tree traversal */
struct b_temp_node {
    bool last;
    b_node * node;
};

void printf_b_node(b_node * node)
{
    if(node)
    {
        linked_queue * q = linked_queue_init();

        struct b_temp_node * root_node = calloc_size_type(1, struct b_temp_node);
        root_node->node = node;
        root_node->last = true;
        linked_queue_offer(q, root_node);

        while (linked_queue_size(q) > 0)
        {
            struct b_temp_node * temp_node = linked_queue_poll(q);
            b_node * n = temp_node->node;

            for (int i = 0; i < n->key_number; ++i) {
                printf("%d", *(int*)n->entries[i]->key);
                if (i < n->key_number - 1)
                    printf("-");
            }

            if (temp_node->last)
                printf("\n");
            else
                printf(", ");

            if (!n->leaf) {
                for (int i = 0; i < 2 * n->t - 1; ++i) {
                    if (n->children[i]) {
                        struct b_temp_node *t_node = malloc_type(struct b_temp_node);
                        t_node->node = n->children[i];

                        if ((i == 2 * n->t - 2 || !n->children[i + 1])
                            && temp_node->last)
                            t_node->last = true;
                        else
                            t_node->last = false;

                        linked_queue_offer(q, t_node);
                    }
                }
            }
            free(temp_node);
        }
        linked_queue_destroy(q);
    }
}

#define b_put(i) \
    printf("put %d--------------------\n", i);    \
    int t##i = i;\
    b_tree_put(tree, &t##i, &t##i); \
    printf_b_node(tree->root);                      \
    printf("depth: %d\n", b_tree_depth(tree));

#define b_remove(i) \
    printf("remove---%d\n", *(int*)b_tree_remove(tree, &t##i)); \
    printf_b_node(tree->root);

void printf_kv(void * k, void * v)
{
    printf("k-v: {%d, %d}\n", *(int*)k, *(int*)v);
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

    b_tree_foreach(tree, printf_kv, IN);

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
    b_put(12)
    b_put(22)
    b_put(13)
    b_tree_destroy(tree);
}

#endif

void b_tree_test()
{
#ifdef  TEST_B_TREE
    b_tree_put_testing();
    b_tree_remove_testing();
#endif
}