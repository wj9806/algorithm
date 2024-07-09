//
// Created by xsy on 2024/7/9.
//

#include "hash_table.h"
#include "common.h"
#include <stdlib.h>

static int hash(hash_table* h, void * key)
{
    if(key == (void*)0) return 0;
    int sh = h->hash_code(h, key);
    return sh ^ (sh >> 16);
}

/* Calculate the hash table index where the key is located */
static unsigned int tab_index(hash_table* h, void * key)
{
    return (h->t_size -1) & hash(h, key);
}

static unsigned int next_power_of_two(unsigned int n) {
    unsigned int p = 1;
    while (p < n && p < MAX_TABLE_SIZE) {
        p <<= 1;
    }
    return p;
}

static entry * create_entry(hash_table * h, void * k, void * v)
{
    entry * e = (entry*) malloc(sizeof(entry));
    e->key = k;
    e->value = v;
    e->next_entry = (entry*)0;
    e->hash = hash(h, k);
    return e;
}

static void table_resize()
{

}

int int_hash_code(hash_table* h, void * key)
{
    return *(int*)key;
}

hash_table * hashtable_init(int (*hash_code)(hash_table* h, void * key))
{
    return hashtable_init_size(hash_code, INIT_TABLE_SIZE);
}

hash_table * hashtable_init_size(int (*hash_code)(hash_table* h, void * key),
                                 int t_size)
{
    hash_table* tab = (hash_table*)malloc(sizeof(hash_table));
    if(tab == (hash_table*)0)
    {
        debug_error("create hash table failed");
        return (hash_table*) 0;
    }
    entry ** table = (entry**) calloc(t_size, sizeof(entry*));
    if(table == (entry**)0)
    {
        debug_error("create hash table failed");
        free(tab);
        return (hash_table*) 0;
    }

    tab->table = table;
    tab->t_size = t_size <= 0 ? INIT_TABLE_SIZE : next_power_of_two(t_size);
    tab->size = 0;
    tab->load_factor = DEFAULT_LOAD_FACTOR;
    tab->hash_code = hash_code;
    return tab;
}

void hashtable_destroy(hash_table * h)
{
    if(!h) return;
    entry * cur, * tmp;
    for (int i = 0; i < h->t_size; ++i)
    {
        cur = h->table[i];
        while (cur != (entry*)0)
        {
            tmp = cur;
            cur = cur->next_entry;
            free(tmp);
        }
        h->table[i] = (entry*)0;
    }

    free(h->table);
    h->table = (entry**)0;
    free(h);
}

void * hashtable_put(hash_table * h, void * k, void * v)
{
    int k_hash = hash(h, k);
    void * old_v = (void*)0; entry * p, * r; unsigned int i;

    if((p = h->table[i = tab_index(h, k)]) == (entry*) 0)
        h->table[i] = create_entry(h, k, v);
    else
    {

        if(p->hash == k_hash
                && k == p->key)
            r = p;
        else
        {
            do {
                if((r = p->next_entry) == (entry*)0) {
                    p->next_entry = create_entry(h, k, v);
                    break;
                } else {
                    if(r->hash == k_hash
                            && k == r->key)
                        break;
                    p = r;
                }
            } while (1);
        }

        if(r != (entry*) 0)
        {
            old_v = r->value;
            r->value = v;
            return old_v;
        }
    }
    h->size++;
    return old_v;
}