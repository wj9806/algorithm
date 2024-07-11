//
// Created by xsy on 2024/7/11.
//

#include "tree_map.h"

/**
 *       Left rotation around p
 *        pp                 pp
 *       /                  /
 *      p                  pr
 *     / \       ==>      / \
 *   pl   pr             p   rr
 *       / \           / \
 *     rl   rr       pl   rl
 */
static void left_rotate(tree_map * map, tree_node * p)
{
    if(!p) {
        tree_node * pr = p->right, * rl, * pp;

        if((pp = p->parent))
        {
            if(pp->left == p)
                pp->left = pr;
            else
                pp->right = pr;
        }
        else
            map->root = pr;

        pr->parent = pp;
        p->parent = pr;

        if((rl = pr->left))
        {
            rl->parent = p;
        }
        p->right = rl;
        pr->left = p;
    }
}

/**
 * Right rotation around p
 *          pp                     pp
 *          /                     /
 *         p                     pl
 *        / \       ==>         / \
 *      pl   pr               ll   p
 *     /  \                       / \
 *   ll  lr                     lr   pr
 */
static void right_rotate(tree_map * map, tree_node * p)
{
    if(!p) {
        tree_node * pl = p->left, * lr, * pp;
        if((pp = p->parent))
        {
            if(pp->left == p)
                pp->left = pl;
            else
                pp->right = pl;
        }
        else
            map->root = pl;

        pl->parent = pp;
        p->parent = pl;

        if((lr = pl->right))
        {
            lr->parent = p;
        }
        p->left = lr;
        pl->right = p;
    }
}

static tree_node * create_node(void * key, void * value, tree_node * parent)
{
    return tree_node_create(parent, (void*)0, (void*)0, BLACK, key, value);
}

static tree_node * parent_of(tree_node * node)
{
    return node ? node->parent : (tree_node *)0;
}

static tree_node * right_of(tree_node * node)
{
    return node ? node->right : (tree_node *)0;
}

static tree_node * left_of(tree_node * node)
{
    return node ? node->left : (tree_node *)0;
}

/* rebalanced of the red and black trees after put elements */
static void rebalanced_after_put(tree_map * m, tree_node * n)
{
    n->color = RED;
    if(n != m->root && n->parent->color == RED)
    {

    }
    m->root->color = BLACK;
}

tree_node * tree_node_create(tree_node * parent, tree_node * left, tree_node * right, color color, void * key, void * value)
{
    tree_node * n = malloc_type(tree_node);
    if(!n)
    {
        debug_error("Failed to create tree_node");
        return (tree_node *) 0;
    }
    n->parent = parent;
    n->left = left;
    n->right = right;
    n->color = color;
    n->key = key;
    n->value = value;
    return n;
}

tree_map * tree_map_init(key_compare compare)
{
    if(!compare)
    {
        debug_error("key_compare cannot be null");
        return (tree_map *) 0;
    }

    tree_map * m = malloc_type(tree_map);
    if(!m)
    {
        debug_error("Failed to create tree_map");
        return (tree_map *) 0;
    }

    tree_node * node = tree_node_create((tree_node*)0, (tree_node*)0, (tree_node*)0,
                                        BLACK, (void*)0, (void*)0);
    if(!node)
    {
        debug_error("Failed to create tree_map");
        free(m);
        return (tree_map *) 0;
    }

    m->root = node;
    m->size = 0;
    m->compare = compare;
    return m;
}

void * tree_map_put(tree_map * m, void * k, void * v)
{
    void * old_v = (void*)0;
    if (!k)
    {
        debug_error("key is null");
        return old_v;
    }

    tree_node * n;
    if(!(n = m->root))
    {
        m->root = create_node(k, v, (void*)0);
        m->size++;
        return old_v;
    }

    //find the insert node of parent
    tree_node * parent; int cmp;
    do {
        parent = n;
        cmp = m->compare(k, parent->key);
        if (cmp < 0)
            n = n->left;
        else if (cmp > 0)
            n = n->right;
        else
        {
            old_v = n->value;
            n->value = v;
            return old_v;
        }
    } while (n);

    tree_node * node = create_node(k, v, parent);
    if(cmp < 0)
        parent->left = node;
    else
        parent->right = node;
    rebalanced_after_put(m, node);
    m->size++;
    return old_v;
}
