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
    b_entry ** entries = malloc_size_type(2 * t, b_entry*);
    if(!entries)
    {
        debug_error("create b_node entries failed");
        free(n);
        return (b_node *)0;
    }

    b_node ** children = malloc_size_type(2 * t -1, b_node*);
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

static void insert_key(b_node * node, void * key, void * value, int index)
{
    b_entry * entry = b_entry_create(key, value);
    if(!entry)
    {
        debug_error("create b_entry failed");
        return;
    }

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

static void * node_put(b_node * node, void * key, void * value)
{
    int i = 0;
    int cmp;
    while (i < node->key_number)
    {
        if((cmp = node->compare(node->entries[i]->key, key)) == 0)
        {
            void * old_value = node->entries[i]->value;
            node->entries[i]->value = value;
            return old_value;
        }
        else if (cmp > 0)
            break;
        i++;
    }
    if(node->leaf)
        insert_key(node, key, value, i);
    else
        //insert into children
        return node_put(node->children[i], key, value);
    return (void *)0;
}

b_tree * btree_init(int t, compare compare)
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
    return btree;
}

bool b_tree_contains_key(b_tree * tree, void * key)
{
    return get_node(tree->root, key) != (b_node*)0;
}

void * b_tree_put(b_tree * tree, void * key, void * value)
{
    return node_put(tree->root, key, value);
}
