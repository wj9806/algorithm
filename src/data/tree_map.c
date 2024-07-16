//
// Created by xsy on 2024/7/11.
//

#include "tree_map.h"
#include "queue.h"
#include <stdio.h>

/* Returns the size of full binary tree */
static int full_tree_size(int depth)
{
    return depth ? (2 << depth) - 1 : 0;
}

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
    if(p) {
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
    if(p) {
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

static color color_of(tree_node * node)
{
    return node ? node->color : BLACK;
}

static void set_color(tree_node * node, color c)
{
    if(node)
        node->color = c;
}

static void pre_order(tree_node * node, bi_consumer consumer)
{
    if(node)
    {
        consumer(node->key, node->value);
        pre_order(node->left, consumer);
        pre_order(node->right, consumer);
    }
}

static void post_order(tree_node * node, bi_consumer consumer)
{
    if(node)
    {
        post_order(node->left, consumer);
        post_order(node->right, consumer);
        consumer(node->key, node->value);
    }
}

static void in_order(tree_node * node, bi_consumer consumer)
{
    if(node)
    {
        in_order(node->left, consumer);
        consumer(node->key, node->value);
        in_order(node->right, consumer);
    }
}

static void level_order(tree_node * node, bi_consumer consumer)
{
    if(node)
    {
        queue* q = queue_init();
        queue_offer(q, node);
        while (queue_size(q) > 0)
        {
            tree_node * n = queue_poll(q);
            consumer(n->key, n->value);

            if (n->left) queue_offer(q, n->left);
            if (n->right) queue_offer(q, n->right);
        }
        queue_destroy(q);
    }
}

/**
 *  rebalanced of the Red-Black tree after put elements
 *
 *  first condition(1) : 2-3-4 tree insert new node and three-node merge  (node has two elements)
 *        P1   black
 *       /           right_rotate P1     P2        black
 *      P2     red     =========>       / \
 *     /                              P3   P1      red
 *    P3       red
 *
 *  first condition(2) :
 *      P1     black                      P1   black
 *     /              left_rotate P2     /            right_rotate P1     P3       black
 *    P2       red      =========>      P3     red      ==========>      / \
 *     \                               /                               P2   P1     red
 *      P3     red                    P2       red
 *
 *  second condition : 2-3-4 tree insert new node and four-node merge  (node has three elements)
 *       P1        black             P1         red
 *      / \                         / \
 *    P2   P3      red    ===>    P2   P3       black
 *          \                          \
 *           P4    red                 P4       red
 */
static void rebalanced_after_put(tree_map * m, tree_node * n)
{
    set_color(n, RED);
    while (n && n != m->root && n->parent->color == RED)
    {
        if(parent_of(n) == left_of(parent_of(parent_of(n))))
        {
            tree_node * y = right_of(parent_of(parent_of(n)));
            if(color_of(y) == RED)
            {
                //second condition
                set_color(parent_of(parent_of(n)), RED);
                set_color(parent_of(n), BLACK);
                set_color(y, BLACK);
                n = parent_of(parent_of(n));
            }
            else
            {
                if(n == right_of(parent_of(n)))
                {
                    //first condition(2)
                    n = parent_of(n);
                    left_rotate(m, n);
                }
                //first condition(1)
                set_color(parent_of(n), BLACK);
                set_color(parent_of(parent_of(n)), RED);
                right_rotate(m, parent_of(parent_of(n)));
            }
        }
        else
        {
            tree_node * y = left_of(parent_of(parent_of(n)));
            if(color_of(y) == RED)
            {
                //second condition
                set_color(parent_of(parent_of(n)), RED);
                set_color(parent_of(n), BLACK);
                set_color(y, BLACK);
                n = parent_of(parent_of(n));
            }
            else
            {
                if(n == left_of(parent_of(n)))
                {
                    //first condition(2)
                    n = parent_of(n);
                    right_rotate(m, n);
                }
                //first condition(1)
                set_color(parent_of(n), BLACK);
                set_color(parent_of(parent_of(n)), RED);
                left_rotate(m, parent_of(parent_of(n)));
            }
        }
    }
    set_color(m->root, BLACK);
}

static int depth(tree_node * node)
{
    if (!node) return 0;

    int left = depth(node->left);
    int right = depth(node->right);
    return left > right ? (left+1) : (right+1);
}

static tree_node * get_node(tree_map * m, void * k)
{
    if (!k) return (void*)0;

    tree_node * n = m->root;
    int cmp;
    while (n)
    {
        cmp = m->compare(k, n->key);
        if (cmp < 0)
            n = n->left;
        else if (cmp > 0)
            n = n->right;
        else
            return n;
    }
    return (void*)0;
}

/**
 * Returns the predecessor of the specified tree node
 */
tree_node * tree_node_predecessor(tree_node * n)
{
    if (!n)
        return (tree_node*)0;
    else if (n->left)
    {
        tree_node * node = n->left;
        while (node->right)
            node = node->right;
        return node;
    }
    else
    {
        tree_node * p = n->parent;
        tree_node * ch = n;

        while (p && ch == p->left)
        {
            ch = p;
            p = p->parent;
        }
        return p;
    }
}

/**
 * Returns the successor of the specified tree node
 */
tree_node * tree_node_successor(tree_node * n)
{
    if (!n)
        return (tree_node*)0;
    else if (n->right)
    {
        tree_node * node = n->right;
        while (node->left)
            node = node->left;
        return node;
    }
    else
    {
        tree_node * p = n->parent;
        tree_node * ch = n;

        while (p && ch == p->right)
        {
            ch = p;
            p = p->parent;
        }
        return p;
    }
}

static void rebalanced_after_remove(tree_map * m, tree_node * node)
{
    while (node != m->root && color_of(node) == BLACK)
    {
        if (node == left_of(parent_of(node)))
        {
            tree_node * sib = right_of(parent_of(node));

            if (color_of(sib) == RED)
            {
                set_color(sib, BLACK);
                set_color(parent_of(sib), RED);
                left_rotate(m, parent_of(sib));
                sib = right_of(parent_of(node));
            }
            if (color_of(left_of(sib)) == BLACK && color_of(right_of(sib)) == BLACK)
            {
                set_color(sib, RED);
                node = parent_of(node);
            }
            else
            {
                if (color_of(right_of(sib)) == BLACK)
                {
                    set_color(left_of(sib), BLACK);
                    set_color(sib, RED);
                    right_rotate(m, sib);
                    sib = right_of(parent_of(node));
                }
                set_color(sib, color_of(parent_of(node)));
                set_color(parent_of(node), BLACK);
                set_color(right_of(sib), BLACK);
                left_rotate(m, parent_of(node));
                node = m->root;
            }
        }
        else
        {
            //symmetric
            tree_node * sib = left_of(parent_of(node));

            if (color_of(sib) == RED)
            {
                set_color(sib, BLACK);
                set_color(parent_of(sib), RED);
                right_rotate(m, parent_of(node));
                sib = left_of(parent_of(node));
            }
            if (color_of(left_of(sib)) == BLACK && color_of(right_of(sib)) == BLACK)
            {
                set_color(sib, RED);
                node = parent_of(node);
            }
            else
            {
                if (color_of(left_of(sib)) == BLACK)
                {
                    set_color(right_of(sib), BLACK);
                    set_color(sib, RED);
                    left_rotate(m, sib);
                    sib = left_of(parent_of(node));
                }
                set_color(sib, color_of(parent_of(node)));
                set_color(parent_of(node), BLACK);
                set_color(left_of(sib), BLACK);
                right_rotate(m, parent_of(node));
                node = m->root;
            }
        }
    }
    //node color is red
    set_color(node, BLACK);
}

static void delete_node(tree_map * m, tree_node * node)
{
    m->size--;
    //has 2 children
    if (node->right && node->left)
    {
        tree_node * s = tree_node_successor(node);
        node->key = s->key;
        node->value = s->value;
        node = s;
    }

    tree_node * replacement = node->left ? node->left : node->right;
    if (replacement)
    {
        // Link replacement to parent
        replacement->parent = node->parent;
        if (!node->parent)
            m->root = replacement;
        else if (node == node->parent->left)
            node->parent->left = replacement;
        else
            node->parent->right = replacement;

        node->parent = node->left = node->right = (void*)0;

        if (node->color == BLACK)
            rebalanced_after_remove(m, replacement);
    }
    else if (!node->parent)
    {
        //delete root node
        m->root = (void*)0;
    }
    else
    {
        //leaf node
        if (node->color == BLACK)
            rebalanced_after_remove(m, node);
        if (node->parent)
        {
            if (node == node->parent->left)
                node->parent->left = (void*)0;
            else if (node == node->parent->right)
                node->parent->right = (void*)0;
            node->parent = (void*)0;
        }
    }

    free(node);
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

void tree_map_destroy(tree_map * m, bool free_key, bool free_value)
{
    tree_map_clear(m, free_key, free_value);
    free(m);
    m = (tree_map*)0;
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

    m->root = (tree_node *) 0;
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

void * tree_map_remove(tree_map * m, void * k)
{
    tree_node * node = get_node(m, k);
    if (!node) return (void*) 0;

    void * v = node->value;
    delete_node(m, node);
    return v;
}

void * tree_map_get(tree_map * m, void * k)
{
    tree_node * node = get_node(m, k);
    return node ? node->value : (void*)0;
}

void tree_map_foreach(tree_map * m, bi_consumer consumer, traversal tra)
{
    if(!m->root) return;

    switch (tra) {
        case LEVEL:
            level_order(m->root, consumer);
            break;
        case PRE:
            pre_order(m->root, consumer);
            break;
        case POST:
            post_order(m->root, consumer);
            break;
        case IN:
        default:
            in_order(m->root, consumer);
    }
}

int tree_map_depth(tree_map * m)
{
    return depth(m->root);
}

struct node_ele
{
    tree_node * node;
    int index;
};

void node_list(tree_map * m, linkedlist * list)
{
    int tree_depth = tree_map_depth(m);
    int full_size = full_tree_size(tree_depth);
    int size = full_size;

    queue* q = queue_init();
    queue_offer(q, m->root);
    while (queue_size(q) > 0 && size--)
    {
        tree_node * n = queue_poll(q);

        if (n)
        {
            struct node_ele * pn = malloc_type(struct node_ele);
            pn->node = n;
            pn->index = full_size - size - 1;
            linkedlist_add(list, pn);
        }

        queue_offer(q, n ? n->left : 0);
        queue_offer(q, n ? n->right : 0);
    }
    queue_destroy(q);
}

static void print_spaces(int count) {
    for (int i = 0; i < count; i++) {
        printf("  ");
    }
}

void tree_map_print(tree_map *map, printf_tree_node func)
{
    int depth = tree_map_depth(map);
    linkedlist * list = linkedlist_init();
    node_list(map, list);

    for (int i = depth, level = 0, all = 0; i > 0; --i, level++) {
        int count = level ? 2 << (level - 1) : 1;
        for (int j = 0; j < count; j++)
        {
            if (j)
                print_spaces((2 << (depth - level)) -1);
            else
                print_spaces((2 << (depth - level - 1)));

            if (!linkedlist_is_empty(list))
            {
                if (((struct node_ele *) linkedlist_first(list))->index == all++)
                {
                    struct node_ele * ne = (struct node_ele *)linkedlist_remove_first(list);
                    func(ne->node);
                    free(ne);
                }
                else
                    func((tree_node*)0);
            }
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

void clear_node(tree_node * node, bool free_key, bool free_value)
{
    if (node)
    {
        clear_node(node->left, free_key, free_value);
        clear_node(node->right, free_key, free_value);

        if (node->key && node->key != node->value)
        {
            if (free_key) free(node->key);
        }

        if (node->value)
        {
            if (free_value && (node->key != node->value || !free_key))
                free(node->value);
        }
        node->left = node->right = node->parent = (void*)0;
        free(node);
        node = (void*)0;
    }
}

void tree_map_clear(tree_map * m, bool free_key, bool free_value)
{
    clear_node(m->root, free_key, free_value);
    m->size = 0;
    m->root = (tree_node *) 0;
}

bool tree_map_contains_key(tree_map * m, void * k)
{
    return get_node(m, k) != (tree_node *)0;
}

tree_node * tree_map_first_node(tree_map * m)
{
    tree_node * node = m->root;
    if (node)
        while (node->left)
            node = node->left;
    return node;
}

tree_node * tree_map_last_node(tree_map * m)
{
    tree_node * node = m->root;
    if (node)
        while (node->right)
            node = node->right;
    return node;
}

void * tree_map_first_key(tree_map * m)
{
    tree_node * node = tree_map_first_node(m);
    return node ? node->key : (void*) 0;
}

void * tree_map_last_key(tree_map * m)
{
    tree_node * node = tree_map_last_node(m);
    return node ? node->key : (void*) 0;
}
