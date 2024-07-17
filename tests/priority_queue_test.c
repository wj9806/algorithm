//
// Created by xsy on 2024/7/16.
//
#include "priority_queue.h"
#include <stdio.h>

#define offer(e) \
    int i##e = e;\
    priority_queue_offer(q, &i##e);

#define print_queue() \
    priority_queue_foreach(q, p)\
    {\
        printf("%d  ", *(int*)p);\
    }\
    printf("\n");

#define poll() \
    printf("poll %d\n", *(int*)priority_queue_poll(q)); \
    print_queue()

void priority_queue_test()
{
#ifdef TEST_PRIORITY_QUEUE
    priority_queue * q = priority_queue_init(10, int_compare);
    offer(100)
    offer(19)
    offer(36)
    offer(17)
    offer(3)
    offer(25)
    offer(1)
    offer(2)
    offer(7)
    offer(4)

    int * p;
    print_queue();

    while (!priority_queue_is_empty(q))
    {
        poll()
    }

    priority_queue_destroy(q, false);
#endif
}
