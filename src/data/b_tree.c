//
// Created by xsy on 2024/7/17.
//

#include <memory.h>
#include <stdio.h>
#include "b_tree.h"

#define in_free(p) \
    free(p)

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
    b_entry** entries = calloc_size_type(2 * t - 1, b_entry*);
    if(!entries)
    {
        debug_error("create b_node entries failed");
        in_free(n);
        return (b_node *)0;
    }

    b_node ** children = calloc_size_type(2 * t, b_node*);
    if(!children)
    {
        debug_error("create b_node children failed");
        in_free(n);
        in_free(entries);
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
    size_t move_size = (node->key_number - index) * sizeof(b_entry*);
    memmove(&node->entries[index + 1], &node->entries[index], move_size);
    node->entries[index] = entry;
    node->key_number++;
}

static void insert_child(b_node * node, b_node * child, int index)
{
    size_t move_size = (node->key_number - index) * sizeof(b_node*);
    if (move_size > 0)
        memmove(node->children + index + 1, node->children + index, move_size);
    node->children[index] = child;
}

/* *
 * split left
 *
 *        5                2|5
 *      /   \    ==>     /  |  \
 *   1|2|3   6          1   3   6
 * */
static void split_node(b_tree * tree, b_node * left, b_node * parent, int index)
{
    int t = left->t;
    if(!parent)
    {
        b_node * root = b_node_create(t, left->compare);
        if(!root) return;

        root->leaf = false;
        insert_child(root, left, 0);
        parent = tree->root = root;
    }

    b_node * right = b_node_create(t, left->compare);
    if(!right) return;
    right->leaf = left->leaf;

    size_t move_size = (t - 1) * sizeof(b_entry *);
    memmove(&right->entries[0], &left->entries[t], move_size);
    for (int i = t ; i < 2 * t -1; ++i) {
        left->entries[i] = (b_entry*)0;
    }

    if(!left->leaf)
    {
        move_size = t * sizeof(b_node *);
        memmove(right->children, left->children + t, move_size);
        for (int i = t; i < left->key_number; i++) {
            left->children[i] = (b_node*)0;
        }
    }

    right->key_number = t - 1;
    left->key_number = t - 1;

    b_entry * mid = left->entries[t - 1];
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

static b_entry * remove_key(b_node * node, int index)
{
    b_entry * entry = node->entries[index];

    size_t move_size = (--node->key_number - index) * sizeof(b_entry *);
    if(move_size > 0)
        memmove(&node->entries[index], &node->entries[index + 1], move_size);
    return entry;
}

static b_entry * remove_leftmost_key(b_node * node)
{
    return remove_key(node, 0);
}

static b_entry * remove_rightmost_key(b_node * node)
{
    return remove_key(node, node->key_number - 1);
}

b_node * remove_child(b_node * node, int index)
{
    b_node * child = node->children[index];

    size_t move_size = (node->key_number - index) * sizeof(b_node *);
    if(move_size > 0)
        memmove(&node->children[index], &node->children[index + 1], move_size);
    node->children[node->key_number] = (b_node *)0;
    return child;
}

b_node * remove_leftmost_child(b_node * node)
{
    return remove_child(node, 0);
}

b_node * remove_rightmost_child(b_node * node)
{
    return remove_child(node, node->key_number);
}

b_node * child_left_sibling(b_node * node, int index)
{
    return index > 0 ? node->children[index - 1] : (b_node*)0;
}

b_node * child_right_sibling(b_node * node, int index)
{
    return index == node->key_number ? (b_node*)0 : node->children[index + 1];
}

void move_to_target(b_node * src, b_node * target) {
    int start = target->key_number;
    if (!src->leaf) {
        for (int i = 0; i <= src->key_number; i++) {
            target->children[start + i] = src->children[i];
        }
    }
    for (int i = 0; i < src->key_number; i++) {
        target->entries[target->key_number++] = src->entries[i];
    }
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

static bool found(b_node * node, int i, int cmp)
{
    return i < node->key_number && cmp == 0;
}

static void rebalanced(b_tree * tree, b_node * parent, b_node * x, int i)
{
    if(x == tree->root) return;
    b_node * left = child_left_sibling(parent, i);
    b_node * right = child_right_sibling(parent, i);

    if(left != (b_node *)0 && left->key_number > tree->min_key_count)
    {
        //right rotate
        insert_entry(x, parent->entries[i - 1], 0);
        if(!left->leaf)
        {
            insert_child(x, remove_rightmost_child(left), 0);
        }
        parent->entries[i - 1] = remove_rightmost_key(left);
        return;
    }

    if(right != (b_node *)0 && right->key_number > tree->min_key_count)
    {
        //left rotate
        insert_entry(x, parent->entries[i], x->key_number);
        if(!right->leaf)
        {
            insert_child(x, remove_leftmost_child(right), x->key_number + 1);
        }
        parent->entries[i] = remove_leftmost_key(right);
        return;
    }

    if (left != (b_node *)0) {
        remove_child(parent, i);
        insert_entry(left, remove_key(parent, i - 1), left->key_number);
        move_to_target(x, left);
    } else {
        remove_child(parent, i + 1);
        insert_entry(x, remove_key(parent, i), x->key_number);
        move_to_target(x, right);
    }
}

static b_entry * remove_entry(b_tree * tree, b_node * parent, b_node * node, int index, void * key)
{
    int i = 0, cmp;
    while (i < node->key_number)
    {
        if((cmp = node->compare(node->entries[i]->key, key)) >= 0)
            break;
        i++;
    }

    b_entry * e;
    if(node->leaf)
    {
        //leaf
        if(!found(node, i, cmp))
            //not find
            return (b_entry *)0;
        else
            //find
            e = remove_key(node, i);
    }
    else
    {
        //not leaf
        if(!found(node, i, cmp))
            //not find
            e = remove_entry(tree, node, node->children[i], i, key);
        else
        {
            //find
            b_node * s = node->children[i+1];
            while (!s->leaf)
                s = s->children[0];
            e = node->entries[i];
            node->entries[i] = s->entries[0];
            remove_entry(tree, node, node->children[i + 1], i + 1, s->entries[0]->key);
        }
    }

    if(node->key_number < tree->min_key_count)
    {
        //rebalanced
        rebalanced(tree, parent, node, index);
    }

    return e;
}

void * b_tree_remove(b_tree * tree, void * key)
{
    b_entry * entry = remove_entry(tree, (b_node*)0, tree->root, 0, key);
    if(entry)
    {
        void * data = entry->value;
        in_free(entry);
        return data;
    }
    return (void*)0;
}

static void clear_b_node(b_node * node, free_func free_key, free_func free_value)
{
    if (node)
    {
        if(!node->leaf)
        {
            for (int i = 0; i < 2 * node->t - 1; ++i)
            {
                if(node->children[i])
                {
                    clear_b_node(node->children[i], free_key, free_value);
                }
                node->children[i] = (void*)0;
            }
        }


        for (int i = 0; i < node->key_number; ++i) {
            b_entry * entry = node->entries[i];
            if (entry)
            {
                debug_info("key:%d", *(int*)entry->key);
                if(free_key || free_value) {
                    if (entry->key)
                        if (free_key) free_key(entry->key);

                    if (entry->value) {
                        if (free_value) free_value(entry->value);
                    }
                }
                in_free(entry);
            }
        }

        printf("node: %p\n", node);
        in_free(node->entries);
        in_free(node->children);
        in_free(node);
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
    in_free(tree);
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

#include "linked_queue.h"

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
            in_free(temp_node);
        }
        linked_queue_destroy(q);
    }
}
#endif