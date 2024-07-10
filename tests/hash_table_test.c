//
// Created by xsy on 2024/7/9.
//
#include "hash_table.h"
#include <stdio.h>

#ifdef TEST_HASH_TABLE

#define print_line  printf("%s\n", "------------------------------------");

void print_tab_func(void * key, void * value)
{
    if((int*)key)
    {
        printf("{%d : %d}   ", *(int*)key, *(int*)value);
    }
    else
    {
        printf("{%s : %d}   ", "null", *(int*)value);
    }
}

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

static void test_put_remove()
{
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
    printf("hashtable size: %d\n", hashtable_size(h));


    printf("hashtable null key: %d\n", *(int*)hashtable_get(h, (int*)0));
    printf("hashtable -3 key: %d\n", *(int*)hashtable_get(h, (int*)&i6));

    hashtable_foreach(h, print_tab_func);

    printf("\nhashtable remove 0: %d\n", *(int*) hashtable_remove(h, &i1));
    debug_hash_table(h);
    printf("\nhashtable remove null: %d\n", *(int*) hashtable_remove(h, (int*)0));
    debug_hash_table(h);

    printf("\nhashtable remove -3: %d\n", *(int*) hashtable_remove(h, &i6));
    debug_hash_table(h);

    hashtable_destroy(h);
    print_line
}

#define put(i, h) \
     int in##i = i;     \
     hashtable_put(h, &in##i, &in##i); \
     debug_hash_table(h);

#define X(i) put(i, h);

#define INDEX_LIST \
    X(1) \
    X(19)           \
    X(3)          \
    X(35)           \
    X(51)       \
    X(6)          \
    X(7)          \
    X(8)          \
    X(9)          \
    X(10)          \
    X(11)          \
    X(12)          \
    X(13)          \
    X(14)          \
    X(15)          \
    X(16)          \
    X(17)          \
    X(18)          \
    X(20)          \
    X(21)          \
    X(22)          \
    X(23)          \
    X(24)          \
    X(32)

static void test_resize()
{
    hash_table * h = hashtable_init_size(int_hash_code, 16);
    INDEX_LIST
    hashtable_destroy(h);
    print_line
}

void hash_table_test()
{
#ifdef TEST_HASH_TABLE
    test_put_remove();
    //test_resize();
#endif
}
