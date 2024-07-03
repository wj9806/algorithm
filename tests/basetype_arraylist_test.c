//
// Created by wj on 2024/7/3.
//

#include "basetype_arraylist.h"
#include "stdio.h"

void int_printf_func(int i)
{
    printf("%d\n", i);
}

void char_printf_func(char c)
{
    printf("%c\n", c);
}

void uint32_t_printf_func(uint32_t u)
{
    printf("%d\n", u);
}


void basetype_arraylist_test()
{
#ifdef TEST_BASETYPE_ARRAY
    int_arraylist * list = int_arraylist_init(2);
    for (int i = 0; i < 5; ++i) {
        int_arraylist_add(list, i);
    }

    int_printf_func(int_arraylist_get(list, 1));
    printf("list size: %d\n", int_arraylist_size(list));
    printf("list capacity: %d\n", int_arraylist_capacity(list));

    int_arraylist_foreach(list, int_printf_func);

    int_arraylist_remove(list, 2);
    printf("---------------------------\n");
    int_arraylist_foreach(list, int_printf_func);

    int_arraylist_destroy(list);


    char_arraylist * list2 = char_arraylist_init(2);
    for (int i = 65; i < 70; ++i) {
        char_arraylist_add(list2, (char)i);
    }
    char_printf_func(char_arraylist_get(list2, 1));
    printf("list size: %d\n", char_arraylist_size(list2));
    printf("list capacity: %d\n", char_arraylist_capacity(list2));

    char_arraylist_foreach(list2, char_printf_func);

    char_arraylist_remove(list2, 2);
    printf("---------------------------\n");
    char_arraylist_foreach(list2, char_printf_func);
    char_arraylist_destroy(list2);

    uint32_t_arraylist * list3 = uint32_t_arraylist_init(2);
    for (int i = 10; i < 15; ++i) {
        uint32_t_arraylist_add(list3, i);
    }

    uint32_t_printf_func(uint32_t_arraylist_get(list3, 1));
    printf("list size: %d\n", uint32_t_arraylist_size(list3));
    printf("list capacity: %d\n", uint32_t_arraylist_capacity(list3));

    uint32_t_arraylist_foreach(list3, uint32_t_printf_func);

    uint32_t_arraylist_remove(list3, 2);
    printf("---------------------------\n");
    uint32_t_arraylist_foreach(list3, uint32_t_printf_func);

    uint32_t_arraylist_destroy(list3);
#endif
}
