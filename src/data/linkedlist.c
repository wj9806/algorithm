//
// Created by wj on 2024/7/3.
//

#include "linkedlist.h"
#include <stdlib.h>
#include "common.h"

linkedlist * linkedlist_init()
{
    linkedlist * list = malloc_type(linkedlist);
    if(!list)
    {
        perror("Failed to create linkedlist");
        return (linkedlist *) 0;
    }

    list->first = list->last = (node *)0;
    list->size = 0;
    return list;
}

void linkedlist_destroy(linkedlist * list)
{
    free(list);
}

void linkedlist_insert_first(linkedlist * list, node * nd)
{
    //set node
    nd->next = list->first;
    nd->pre = (node*)0;

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
}

void linkedlist_insert_last(linkedlist * list, node * nd)
{
    //set node
    nd->next = (node*)0;
    nd->pre = list->last;

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
}

node * linkedlist_remove_first(linkedlist * list)
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

    removed_node->pre = removed_node->next = (node *)0;
    return removed_node;
}

node * linkedlist_remove_last(linkedlist * list)
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

    removed_node->pre = removed_node->next = (node *)0;
    return removed_node;
}

node * linkedlist_remove(linkedlist * list, node * nd)
{
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
    list->size--;
    return nd;
}

void linkedlist_insert_after(linkedlist * list, node * pre, node * nd)
{
    if (linkedlist_is_empty(list) || !pre)
    {
        linkedlist_insert_first(list, nd);
        return;
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
}