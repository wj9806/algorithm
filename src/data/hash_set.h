//
// Created by xsy on 2024/7/10.
//

#ifndef ALGORITHM_HASH_SET_H
#define ALGORITHM_HASH_SET_H

#include "hash_table.h"

typedef struct {
    hash_table * ht;
} hash_set;

hash_set * hashset_init(long (*hash_code)(hash_table* h, void * key));

hash_set * hashset_init_size(long (*hash_code)(hash_table* h, void * key), int t_size);

/**
 * Adds the specified element to this set if it is not already present.
 * @return true if this set did not already contain the specified
 */
bool hashset_add(hash_set * set, void * value);

/**
 * Removes the specified element from this set if it is present.
 * true if the set contained the specified element
 */
bool hashset_remove(hash_set * set, void * value);

/**
 * Removes all of the elements from this set.
 * The set will be empty after this call returns.
 */
void hashset_clear(hash_set * set);

/**
 * destroy the hashset
 */
void hashset_destroy(hash_set * set);

/**
 * Returns {@code true} if this set contains the specified element.
 */
bool hashset_contains(hash_set * set, void * value);

/* Returns hash set size */
static inline unsigned int hashset_size(hash_set * set)
{
    return set->ht->size;
}

/* Returns true if this hash set is empty */
static inline bool hashset_is_empty(hash_set * set)
{
    return !set || set->ht->size == 0;
}

#endif //ALGORITHM_HASH_SET_H
