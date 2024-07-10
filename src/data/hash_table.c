//
// Created by xsy on 2024/7/9.
//

#include "hash_table.h"
#include "common.h"
#include <stdlib.h>
#include <limits.h>

static long hash(hash_table* h, void * key)
{
    if(key == (void*)0) return 0;
    long sh = h->hash_code(h, key);
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

/* resize the hashtable */
static void table_resize(hash_table* h)
{
    unsigned int new_t_size, old_t_size = h->t_size;
    int new_thr = 0;
    if(old_t_size >= MAX_TABLE_SIZE)
    {
        h->threshold = INT_MAX;
        return;
    } else if((new_t_size = old_t_size << 1) < MAX_TABLE_SIZE)
    {

        new_thr = h->threshold << 1;
    }
    if(new_thr == 0)
    {
        float ft = (float) new_t_size * h->load_factor;
        new_thr = (new_t_size < MAX_TABLE_SIZE && ft < MAX_TABLE_SIZE) ? (int) ft : INT_MAX;
    }
    h->threshold = new_thr;
    h->t_size = new_t_size;

    entry ** old_table = h->table;
    //alloc new array
    entry ** new_table = (entry**)calloc(h->t_size, sizeof(entry*));

    for (int i = 0; i < old_t_size; ++i) {
        entry * e;
        if((e = old_table[i]) != (entry *)0)
        {
            old_table[i] = (entry *)0;
            if(e->next_entry == (entry *)0)
            {
                new_table[e->hash & (new_t_size - 1)] = e;
            }
            else
            {
                entry * next;
                entry * lo_head = (entry*)0, * lo_tail = (entry*)0;
                entry * hi_head = (entry*)0, * hi_tail = (entry*)0;
                do {
                    next = e->next_entry;

                    //Calculate whether the node falls on the original index
                    if((e->hash & old_t_size) == 0)
                    {
                        if(lo_head == (entry*)0)
                            lo_head = e;
                        else
                            lo_tail->next_entry = e;
                        lo_tail = e;
                    }
                    else
                    {
                        if(hi_head == (entry*)0)
                            hi_head = e;
                        else
                            hi_tail->next_entry = e;
                        hi_tail = e;
                    }
                } while ((e = next) != (entry *)0);

                if(lo_tail != (entry*)0)
                {
                    lo_tail->next_entry = (entry*)0;
                    new_table[i] = lo_head;
                }
                if(hi_tail != (entry*)0)
                {
                    hi_tail->next_entry = (entry*)0;
                    new_table[i + old_t_size] = hi_head;
                }
            }
        }
    }

    free(old_table);
    h->table = new_table;
}

long int_hash_code(hash_table* h, void * key)
{
    return *(int*)key;
}

long void_hash_code(hash_table* h, void * key)
{
    return (long)(uintptr_t)key;
}

hash_table * hashtable_init(long (*hash_code)(hash_table* h, void * key))
{
    return hashtable_init_size(hash_code, INIT_TABLE_SIZE);
}

hash_table * hashtable_init_size(long (*hash_code)(hash_table* h, void * key),
                                 int t_size)
{
    hash_table* tab = (hash_table*)malloc(sizeof(hash_table));
    if(tab == (hash_table*)0)
    {
        debug_error("create hash table failed");
        return (hash_table*) 0;
    }
    tab->t_size = t_size <= 0 ? INIT_TABLE_SIZE : next_power_of_two(t_size);
    entry ** table = (entry**) calloc(tab->t_size, sizeof(entry*));
    if(table == (entry**)0)
    {
        debug_error("create hash table failed");
        free(tab);
        return (hash_table*) 0;
    }

    tab->table = table;
    tab->size = 0;
    tab->load_factor = DEFAULT_LOAD_FACTOR;
    tab->hash_code = hash_code;
    tab->threshold = (int)((float)tab->t_size * tab->load_factor);
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
    long k_hash = hash(h, k);
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

        //replace old value
        if(r != (entry*) 0)
        {
            old_v = r->value;
            r->value = v;
            return old_v;
        }
    }
    if(h->size++ > h->threshold)
    {
        table_resize(h);
    }
    return old_v;
}