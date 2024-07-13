//
// Created by wj on 2024/7/3.
//

#include "linkedlist.h"
#include <stdlib.h>
#include "common.h"

linkedlist * linkedlist_init()
{
    return linkedlist_init_capacity(INT_MAX);
}

linkedlist * linkedlist_init_capacity(int capacity)
{
    linkedlist * list = malloc_type(linkedlist);
    if(!list)
    {
        debug_error("Failed to create linkedlist");
        return (linkedlist *) 0;
    }

    list->first = list->last = (node *)0;
    list->size = 0;
    list->capacity = capacity;
    return list;

}

void linkedlist_destroy(linkedlist * list)
{
    node * n, * head = list->first;
    while (head)
    {
        n = head->next;
        free(head);
        head = n;
    }
    free(list);
}

bool linkedlist_insert_first(linkedlist * list, void * data)
{
    if (list->size >= list->capacity)
    {
        debug_warn("linkedlist is full: %d >= %d", list->size >= list->capacity);
        return false;
    }

    node * nd = (node *) malloc(sizeof(node));

    //set node
    nd->next = list->first;
    nd->pre = (node*)0;
    nd->data = data;

    //set list
    if (linkedlist_is_empty(list))
    {
        list->last = list->first = nd;
    }
    else
    {
        list->first->pre = nd;
        list->first = nd;
    }
    list->size++;
    return true;
}

bool linkedlist_insert_last(linkedlist * list, void * data)
{
    if (list->size >= list->capacity)
    {
        debug_warn("linkedlist is full: %d >= %d", list->size >= list->capacity);
        return false;
    }
    node * nd = (node *) malloc(sizeof(node));

    //set node
    nd->next = (node*)0;
    nd->pre = list->last;
    nd->data = data;

    //set list
    if (linkedlist_is_empty(list))
    {
        list->last = list->first = nd;
    }
    else
    {
        list->last->next = nd;
        list->last = nd;
    }
    list->size++;
    return true;
}

void * linkedlist_remove_first(linkedlist * list)
{
    if (linkedlist_is_empty(list))
    {
        return (node *)0;
    }

    node * removed_node = list->first;
    list->first = list->first->next;
    if (list->first == (node *)0)
    {
        list->last = (node *)0;
    }
    else
    {
        removed_node->next->pre = (node *)0;
    }
    list->size--;

    void * data = removed_node->data;
    removed_node->pre = removed_node->next = (node *)0;
    removed_node->data = (void *)0;
    free(removed_node);
    return data;
}

void * linkedlist_remove_last(linkedlist * list)
{
    if (linkedlist_is_empty(list))
    {
        return (node *)0;
    }

    node * removed_node = list->last;
    list->last = list->last->pre;
    if (list->last == (node *)0)
    {
        list->first = (node *)0;
    }
    else
    {
        removed_node->pre->next = (node *)0;
    }
    list->size--;

    void * data = removed_node->data;
    removed_node->pre = removed_node->next = (node *)0;
    removed_node->data = (void *)0;
    free(removed_node);
    return data;
}

static node * find_node(linkedlist * list, void * data)
{
    node * nd;
    linkedlist_for_each(nd, list)
    {
        if (nd->data == data)
        {
            return nd;
        }
    }

    return (node *) 0;
}

bool linkedlist_remove(linkedlist * list, void * data)
{
    node * nd = find_node(list, data);
    if (nd == (node *)0)
    {
        return false;
    }

    if (nd == list->first)
    {
        list->first = nd->next;
    }
    if (nd == list->last)
    {
        list->last = nd->pre;
    }

    if (nd->pre)
    {
        nd->pre->next = nd->next;
    }

    if (nd->next)
    {
        nd->next->pre = nd->pre;
    }

    nd->pre = nd->next = (node *)0;
    nd->data = (void *)0;
    free(nd);
    list->size--;
    return true;
}

bool linkedlist_insert_after(linkedlist * list, void * pre_data, void * cur_data)
{
    if (list->size >= list->capacity)
    {
        debug_warn("linkedlist is full: %d >= %d", list->size >= list->capacity);
        return false;
    }

    node * pre = find_node(list, pre_data);
    if (pre == (node *)0)
    {
        return false;
    }

    node * nd = (node *) malloc(sizeof(node));
    nd->data = cur_data;


    if (linkedlist_is_empty(list))
    {
        linkedlist_insert_first(list, nd);
        return true;
    }

    nd->next = pre->next;
    nd->pre = pre;
    if (pre->next)
    {
        pre->next->pre = nd;
    }
    pre->next = nd;
    if (list->last == pre)
    {
        list->last = nd;
    }
    list->size++;

    return true;
}

bool linkedlist_contains(linkedlist * list, void * data)
{
    node * nd = find_node(list, data);
    return nd != (node*)0;
}