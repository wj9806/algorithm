//
// Created by xsy on 2024/7/9.
//
#include "hash_table.h"
#include <stdio.h>

#ifdef TEST_HASH_TABLE

void debug_hash_table(hash_table * h)
{
    printf("hash_table:\n");
    entry * curr;
    for (int i = 0; i < h->t_size; ++i) {
        printf("    %d: ", i);
        curr = h->table[i];
        while (curr != (entry*)0)
        {
            if((int*)curr->key)
            {
                printf("{%d : %d}   ", *(int*)curr->key, *(int*)curr->value);
            }
            else
            {
                printf("{%s : %d}   ", "null", *(int*)curr->value);
            }

            curr = curr->next_entry;
        }
        printf("\n");
    }
}

#else
#define debug_hash_table(h)
#endif

void hash_table_test()
{
#ifdef TEST_HASH_TABLE
    hash_table * h = hashtable_init(int_hash_code);

    int i1 = 0;
    int i2 = 1;
    int i3 = 2;
    int i4 = 3;
    int i5 = -5;
    int i6 = -3;

    int v = 100;
    int v2 = 200;

    hashtable_put(h, &i1, &v);
    hashtable_put(h, &i2, &v);
    hashtable_put(h, &i3, &v);
    hashtable_put(h, &i4, &v);
    hashtable_put(h, &i5, &v);
    hashtable_put(h, &i6, &v);
    debug_hash_table(h);
    hashtable_put(h, &i3, &v2);
    hashtable_put(h, (int*)0, &v2);
    debug_hash_table(h);
    printf("hashtable size: %d", hashtable_size(h));
    hashtable_destroy(h);
#endif
}
