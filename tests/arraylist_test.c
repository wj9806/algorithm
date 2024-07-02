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


    arraylist_foreach(list, ele_printf);

    printf("list size: %d\n", arraylist_size(list));
    printf("list capacity: %d\n", arraylist_capacity(list));
    arraylist_destroy(list);
#endif
}
