//
// Created by wj on 2024/7/2.
//

#include "arraylist.h"
#include <stdio.h>

typedef struct {
    int i;
} ele;

void ele_printf(void * data)
{
    printf("%d\n", ((ele*)data)->i);
}

void int_printf(void * data)
{
    printf("%d\n", *(int*)data);
}

void arraylist_test()
{
#ifdef TEST_ARRAY
    arraylist * list = arraylist_init(1);

    ele e1;
    e1.i = 1;
    arraylist_add(list, &e1);

    ele e2;
    e2.i = 2;
    arraylist_add(list, &e2);

    ele e3;
    e3.i = 3;
    arraylist_add(list, &e3);

    ele_printf(arraylist_get(list, 2));

    ele * e = arraylist_get_bytype(list, 2, ele);
    printf("arraylist_get_bytype  %d\n", e->i);

    printf("e2 indexof %d\n", arraylist_indexof(list, &e2));
    arraylist_foreach(list, ele_printf);

    printf("list size: %d\n", arraylist_size(list));
    printf("list capacity: %d\n", arraylist_capacity(list));

    ele_printf(arraylist_remove(list, 2));
    ele_printf(arraylist_remove(list, 1));

    printf("list size: %d\n", arraylist_size(list));
    printf("list capacity: %d\n", arraylist_capacity(list));

    arraylist_destroy(list);

    int arr[] = {1, 2, 3, 4};
    arraylist * list2 = arraylist_init(4);
    for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); ++i) {
        arraylist_add(list2, &arr[i]);
    }
    arraylist_foreach(list2, int_printf);

    int i = 5;
    arraylist_insert(list2, 2, &i);
    arraylist_foreach(list2, int_printf);
#endif
}
