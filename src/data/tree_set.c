//
// Created by xsy on 2024/7/16.
//

#include "tree_set.h"

static struct EMPTY_STRUCT {} S;
static void * VALUE = &S;

tree_set * tree_set_init(key_compare compare)
{
    tree_set * set = malloc_type(tree_set);
    if (!set)
    {
        debug_error("create tree_set failed");
        return (tree_set *) 0;
    }
    tree_map * m = tree_map_init(compare);
    if (!m)
    {
        debug_error("create tree_map failed");
        free(set);
        return (tree_set *) 0;
    }
    set->m = m;
    return set;
}

bool tree_set_add(tree_set * set, void * value)
{
    return tree_map_put(set->m, value, VALUE) == (void *)0;
}

bool tree_set_remove(tree_set * set, void * value)
{
    return tree_map_remove(set->m, value) == (void*)0;
}

void * tree_set_first(tree_set * set)
{
    return tree_map_first_key(set->m);
}

void * tree_set_last(tree_set * set)
{
    return tree_map_last_key(set->m);
}

void tree_set_clear(tree_set * set, bool value)
{
    tree_map_clear(set->m, value, false);
}

void tree_set_destroy(tree_set * set, bool value)
{
    tree_map_destroy(set->m, value, false);
    set->m = (tree_map *)0;
    free(set);
    set = (tree_set *)0;
}

bool tree_set_contains(tree_set * set, void * value)
{
    return tree_map_contains_key(set->m, value);
}


