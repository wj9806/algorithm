//
// Created by xsy on 2024/7/10.
//

#include "hash_set.h"

struct EMPTY_STRUCT {} S;
static void * VALUE = &S;

hash_set * hashset_init(long (*hash_code)(hash_table* h, void * key))
{
    return hashset_init_size(hash_code, INIT_TABLE_SIZE);
}

hash_set * hashset_init_size(long (*hash_code)(hash_table* h, void * key), int t_size)
{
    hash_set * set = malloc_type(hash_set);
    if (!set)
    {
        debug_error("create hash set failed");
        return (hash_set*) 0;
    }
    hash_table * table = hashtable_init_size(hash_code, t_size);
    if (!table)
    {
        debug_error("create hash set failed");
        free(set);
        return (hash_set*) 0;
    }
    set->ht = table;
    return set;
}

bool hashset_add(hash_set * set, void * value)
{
    return hashtable_put(set->ht, value, VALUE) == (void *) 0;
}

bool hashset_remove(hash_set * set, void * value)
{
    return hashtable_remove(set->ht, value) == VALUE;
}

void hashset_clear(hash_set * set)
{
    hashtable_clear(set->ht);
}

void hashset_destroy(hash_set * set)
{
    hashtable_destroy(set->ht);
    set->ht = (hash_table *) 0;
    free(set);
}

bool hashset_contains(hash_set * set, void * value)
{
    return hashtable_contains_key(set->ht, value);
}
