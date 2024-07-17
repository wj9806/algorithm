//
// Created by xsy on 2024/7/16.
//

#include "priority_queue.h"

priority_queue * priority_queue_init(int capacity, compare comparator)
{
    priority_queue * q = malloc_type(priority_queue);
    if(!q)
    {
        debug_error("Failed to create priority_queue");
        return (priority_queue *) 0;
    }

    q->data = malloc_size_type(capacity, E);
    if (!q->data) {
        debug_error("Failed to allocate data array");
        free(q);
        return (priority_queue *) 0;
    }

    q->capacity = capacity;
    q->size = 0;
    q->comparator = comparator;
    return q;
}

static void free_array_ele(const priority_queue *q, bool free_ele) {
    if(free_ele)
    {
        for (int i = 0; i < q->size; ++i) {
            ELE e = q->data[i];
            if(e)
                free(e);
        }
    }
}

void priority_queue_destroy(priority_queue * q, bool free_ele)
{
    free_array_ele(q, free_ele);
    free(q->data);
    free(q);
}

bool priority_queue_offer(priority_queue * q, E data)
{

    if(q->capacity == q->size)
        return false;

    int child = q->size++;
    int parent = (child - 1) / 2;

    while (child > 0 && q->comparator(data, q->data[parent]) > 0)
    {
        q->data[child] = q->data[(parent)];
        child = parent;
        parent = (child - 1) / 2;
    }
    q->data[child] = data;
    return true;
}

static void swap_ele(priority_queue * q, int i, int j)
{
    E e = q->data[i];
    q->data[i] = q->data[j];
    q->data[j] = e;
}

/**
 * ele down
 */
static void ele_down(priority_queue * q, int parent)
{
    int left = 2 * parent + 1;
    int right = left + 1;

    int max = parent;
    if(left < q->size && q->comparator(q->data[left], q->data[max]) > 0)
        max = left;
    if(right < q->size && q->comparator(q->data[right], q->data[max]) > 0)
        max = right;
    if(max != parent)
    {
        swap_ele(q, max, parent);
        ele_down(q, max);
    }
}

E priority_queue_poll(priority_queue * q)
{
    if(priority_queue_is_empty(q))
        return (E) 0;
    //swap
    swap_ele(q, 0, --q->size);
    E e = q->data[q->size];
    q->data[q->size] = (void*)0;
    ele_down(q, 0);
    return e;
}

E priority_queue_peek(priority_queue * q)
{
    return priority_queue_is_empty(q) ? (E)0 : (E)q->data[0];
}

void priority_queue_clear(priority_queue * q, bool free_ele)
{
    free_array_ele(q, free_ele);
    q->size = 0;
}
