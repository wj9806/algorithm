//
// Created by xsy on 2024/7/9.
//

#ifndef ALGORITHM_HASH_TABLE_H
#define ALGORITHM_HASH_TABLE_H

#define INIT_TABLE_SIZE         (1<<3)
#define MAX_TABLE_SIZE          (1<<30)
#define DEFAULT_LOAD_FACTOR     0.75f

#include <stdint.h>

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
    long (*hash_code)(struct hash_table* h, void * key);
    /* The next size value at which to resize (t_size * load factor). */
    int threshold;
} hash_table;

long int_hash_code(hash_table* h, void * key);

long void_hash_code(hash_table* h, void * key);

/* init hash table */
hash_table * hashtable_init(long (*hash_code)(hash_table* h, void * key));

/* init hash table with table size */
hash_table * hashtable_init_size(long (*hash_code)(hash_table* h, void * key), int t_size);

/* destroy hash table */
void hashtable_destroy(hash_table * h);

/* put k v*/
void * hashtable_put(hash_table * h, void * k, void * v);

/* Returns hash table size */
static inline unsigned int hashtable_size(hash_table * h)
{
    return h->size;
}

#endif //ALGORITHM_HASH_TABLE_H
