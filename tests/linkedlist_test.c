//
// Created by xsy on 2024/7/8.
//
#include "linkedlist.h"
#include <stdio.h>

typedef struct {
    int i;
} obj;

void linkedlist_test()
{
#ifdef TEST_LINKED_TEST
    linkedlist * list = linkedlist_init();
    obj o1 = {1};
    obj o2 = {2};
    obj o3 = {3};
    obj o4 = {4};

    linkedlist_add(list, &o1);
    linkedlist_add(list, &o2);
    linkedlist_add(list, &o3);

    assert(linkedlist_contains(list, &o1), "linkedlist_contains error")
    assert(!linkedlist_contains(list, &o4), "linkedlist_contains error")
    assert(linkedlist_size(list) == 3, "linkedlist_size error")
    assert(linkedlist_remove(list, &o1), "linkedlist_remove error")
    assert(!linkedlist_remove(list, &o4), "linkedlist_remove error")

    node* node;
    linkedlist_for_each(node, list)
    {
        obj * o = (obj *)node->data;
        printf("%d\n", o->i);
    }

    linkedlist_destroy(list);
#endif
}
