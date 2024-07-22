//
// Created by xsy on 2024/7/17.
//

#include <memory.h>
#include "b_tree.h"

static b_entry * b_entry_create(void * key, void * value)
{
    b_entry * e = malloc_type(b_entry);
    if(!e)
    {
        debug_error("create b_entry failed");
        return (b_entry *)0;
    }

    e->key = key;
    e->value = value;
    return e;
}

static b_node * b_node_create(int t, compare compare)
{
    b_node * n = malloc_type(b_node);
    if(!n)
    {
        debug_error("create b_node failed");
        return (b_node *)0;
    }
    b_entry** entries = malloc_size_type(2 * t, b_entry*);
    if(!entries)
    {
        debug_error("create b_node entries failed");
        free(n);
        return (b_node *)0;
    }

    b_node ** children = calloc_size_type(2 * t -1, b_node*);
    if(!children)
    {
        debug_error("create b_node children failed");
        free(n);
        free(entries);
        return (b_node *)0;
    }
    n->t = t;
    n->leaf = true;
    n->key_number = 0;
    n->entries = entries;
    n->children = children;
    n->compare = compare;
    return n;
}

static b_node * get_node(b_node * node, void * key)
{
    int i = 0;
    int cmp;
    while (i < node->key_number)
    {
        if((cmp = node->compare(node->entries[i]->key, key)) == 0)
            return node;
        else if (cmp > 0)
            break;
        i++;
    }
    if(node->leaf)
        return (b_node *)0;
    return get_node(node->children[i], key);
}

static void insert_entry(b_node * node, b_entry * entry, int index)
{
    size_t move_size = (node->key_number - index) * sizeof(void*);
    memmove(&node->entries[index + 1], &node->entries[index], move_size);
    node->entries[index] = entry;
    node->key_number++;
}

static void insert_child(b_node * node, b_node * child, int index)
{
    size_t move_size = (node->key_number - index) * sizeof(b_node*);
    memmove(&node->children[index + 1], &node->children[index], move_size);
    node->children[index] = child;
}

/* *
 * split node
 *
 *        5                2|5
 *      /   \    ==>     /  |  \
 *   1|2|3   6          1   3   6
 * */
static void split_node(b_tree * tree, b_node * node, b_node * parent, int index)
{
    int t = node->t;
    if(!parent)
    {
        b_node * root = b_node_create(t, node->compare);
        if(!root) return;

        root->leaf = false;
        insert_child(root, node, 0);
        parent = tree->root = root;
    }

    b_node * right = b_node_create(t, node->compare);
    if(!right) return;
    right->leaf = node->leaf;

    size_t move_size = (t - 1) * sizeof(b_entry *);
    memmove(&right->entries[0], &node->entries[t], move_size);

    if(!node->leaf)
    {
        move_size = t * sizeof(b_node *);
        memmove(&right->children[0], &node->children[t], move_size);
        memset(&node->children[t], 0, move_size);
    }

    right->key_number = t - 1;
    node->key_number = t - 1;

    b_entry * mid = node->entries[t - 1];
    insert_entry(parent, mid, index);

    insert_child(parent, right, index + 1);
}

static void * node_put(b_tree * tree, b_node * node, void * key, void * value, b_node * parent, int index)
{
    int i = 0;
    int cmp;
    void * old_value = (void *)0;
    while (i < node->key_number)
    {
        if((cmp = node->compare(node->entries[i]->key, key)) == 0)
        {
            old_value = node->entries[i]->value;
            node->entries[i]->value = value;
            return old_value;
        }
        else if (cmp > 0)
            break;
        i++;
    }
    if(node->leaf)
    {
        b_entry * entry = b_entry_create(key, value);
        if(!entry)
        {
            debug_error("create b_entry failed");
            return (void *)0;
        }
        insert_entry(node, entry, i);
    }
    else
        //insert into children
        old_value = node_put(tree, node->children[i], key, value, node, i);
    if(node->key_number == tree->max_key_count)
    {
        split_node(tree, node, parent, index);
    }
    return old_value;
}

b_tree * btree_init(int t, compare compare, free_func key_free, free_func value_free)
{
    if(t < 2)
    {
        debug_error("t must be greater than 1");
        return (b_tree *)0;
    }
    b_tree * btree = malloc_type(b_tree);
    if(!btree)
    {
        debug_error("create b_tree failed");
        return (b_tree*)0;
    }
    btree->size = 0;
    btree->compare = compare;
    btree->root = (b_node*) 0;
    btree->t = t;
    btree->min_key_count = t - 1;
    btree->max_key_count = (t << 1) - 1;
    btree->key_free = key_free;
    btree->value_free = value_free;
    return btree;
}

bool b_tree_contains_key(b_tree * tree, void * key)
{
    return get_node(tree->root, key) != (b_node*)0;
}

void * b_tree_put(b_tree * tree, void * key, void * value)
{
    if(!tree->root)
        tree->root = b_node_create(tree->t, tree->compare);
    return node_put(tree, tree->root, key, value, (b_node*)0, 0);
}

static void clear_b_node(b_node * node, free_func free_key, free_func free_value)
{
    if (node)
    {
        if(!node->leaf)
        {
            for (int i = 0; i < 2 * node->t - 1; ++i)
                if(node->children[i])
                    clear_b_node(node->children[i], free_key, free_value);
        }

        if(free_key || free_value)
        {
            for (int i = 0; i < node->key_number; ++i) {
                b_entry * entry = node->entries[i];
                if (entry->key)
                    if (free_key) free_key(entry->key);

                if (entry->value)
                    if (free_value) free_value(entry->value);
            }
        }

        free(node->entries);
        free(node->children);
        free(node);
        node = (void*)0;
    }
}

void b_tree_clear(b_tree * tree)
{
    clear_b_node(tree->root, tree->key_free, tree->value_free);
    tree->size = 0;
    tree->root = (b_node *) 0;
}

void b_tree_destroy(b_tree * tree)
{
    b_tree_clear(tree);
    free(tree);
    tree = (void*)0;
}

int b_tree_depth(b_tree * m)
{
    int d = 0;
    b_node * node;
    if(!(node = m->root))
        return d;
    d++;
    while (!node->leaf)
    {
        node = node->children[0];
        d++;
    }

    return d;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ b-tree test ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#ifdef  TEST_B_TREE

#include <stdio.h>
#include "linked_queue.h"

struct b_temp_node {
    b_node * node;
    bool last;
};

void printf_b_node(b_node * node)
{
    if(node)
    {
        linked_queue * q = linked_queue_init();

        struct b_temp_node * root_node = malloc_type(struct b_temp_node);
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

void b_tree_node_test()
{

#define entry(i) \
    int t##i = i;            \
    b_entry * entry##i = b_entry_create(&t##i, &t##i);


    entry(1)
    entry(2)
    entry(3)
    entry(5)
    entry(6)

    int t = 2;
    b_tree * tree = btree_init(t, int_compare, 0, 0);
    if(tree)
    {
        b_node * node = b_node_create(tree->t, tree->compare);
        tree->root = node;

        node->leaf = false;
        node->entries[0] = entry5;
        node->key_number = 1;

        b_node * node1 = b_node_create(tree->t, tree->compare);
        node->children[0] = node1;
        node->children[0]->entries[0] = entry1;
        node->children[0]->entries[1] = entry2;
        node->children[0]->entries[2] = entry3;
        node->children[0]->key_number = 3;

        b_node * node2 = b_node_create(tree->t, tree->compare);
        node->children[1] = node2;
        node->children[1]->entries[0] = entry6;
        node->children[1]->key_number = 1;

        printf_b_node(tree->root);

        printf("------------split--------------\n");
        split_node(tree, tree->root->children[0], tree->root, 0);
        printf_b_node(tree->root);
    }
    b_tree_destroy(tree);
}
#endif