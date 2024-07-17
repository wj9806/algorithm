//
// Created by xsy on 2024/7/9.
//

#ifndef ALGORITHM_HASH_TABLE_H
#define ALGORITHM_HASH_TABLE_H

#define INIT_TABLE_SIZE         (1<<3)
#define MAX_TABLE_SIZE          (1<<30)
#define DEFAULT_LOAD_FACTOR     0.75f

#include <stdint.h>
#include "common.h"
#include "function.h"

typedef struct entry {
    void * key;
    void * value;
    struct entry * next_entry;
    long hash;
} entry;

/**
 * A hashtable that solves hash conflicts based on the chain address method
 */
typedef struct hash_table {
    /* hash table */
    entry ** table;
    /* number of slots in hash table */
    unsigned int t_size;
    /* number of elements in hash table */
    unsigned int size;
    /* load factor */
    float load_factor;
    /* hash code function */
    hash_code hash_code;
    /* The next size value at which to resize (t_size * load factor). */
    int threshold;
} hash_table;

/* init hash table */
hash_table * hashtable_init(hash_code hash_code);

/* init hash table with table size */
hash_table * hashtable_init_size(hash_code hash_code, int t_size);

/* destroy hash table */
void hashtable_destroy(hash_table * h);

/* Removes all of the entry from this map */
void hashtable_clear(hash_table * h);

/* put k v*/
void * hashtable_put(hash_table * h, void * k, void * v);

/**
 * Returns the value to which the specified key is mapped,
 * or null if this map contains no mapping for the key.
 */
void * hashtable_get(hash_table * h, void * k);

/**
 * Removes the mapping for the specified key from this map if present.
 */
void * hashtable_remove(hash_table * h, void * k);

/**
 * Returns true if this map contains a mapping for the
 * specified key.
 */
bool hashtable_contains_key(hash_table * h, void * k);

/**
 * Performs the given action for each entry in this map until all entries have been processed
 */
void hashtable_foreach(hash_table * h, bi_consumer consumer);

/* Returns hash table size */
static inline unsigned int hashtable_size(hash_table * h)
{
    return h->size;
}

/* Returns true if this hash table is empty */
static inline bool hashtable_is_empty(hash_table * h)
{
    return !h || h->size == 0;
}

#endif //ALGORITHM_HASH_TABLE_H
