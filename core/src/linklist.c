#include <stdio.h>
#include <string.h>
#include "linklist.h"

void llist_init(llist *list, const size_t t)
{
    list->type = t;
    list->head = NULL;
}

int llist_append_value(llist *list, const void *value)
{
    if (!list->head)
    {
        return ll_node_init(&list->head, list->type, value);
    }

    ll_node *tail = last(list->head);
    
    return ll_node_init(&tail->next, list->type, value);
}

int llist_append_node(llist *list, ll_node *node)
{
    if (!list->head)
    {
        list->head = node;
        return 0;
    }

    ll_node *tail = last(list->head);
    tail->next = node;
    
    return 0;
}

int llist_remove_node(llist *list, ll_node *node)
{
    if (!list->head || !node)
    {
        puts("Empty list or null node");
        return -1;
    }

    ll_node *current = list->head;
    if (current==node)
    {
        list->head = current->next;
        current->next = NULL;
        return 0;
    }

    ll_node *n = current->next;
    while(n)
    {
        if (n==node)
        {
            current->next = n->next;
            n->next = NULL;
            return 0;
        }

        current = n;
        n = n->next;
    }    

    puts("Node not found");
    return -1;
}

int llist_pop(llist *list)
{
    if (!list->head)
    {
        puts("Pop failed");
        return -1;
    }

    ll_node *new_head = list->head->next;
    ll_node_clear(&list->head);
    list->head = new_head;

    return 0;
}

void llist_reverse_iterative(llist *list)
{
    ll_node *prev = NULL;
    ll_node *current = list->head;
    ll_node *next = NULL;

    while(current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;
}

void llist_reverse_recursive(llist *list)
{
    list->head = reverse_recursive(list->head, NULL);
}

ll_node *reverse_recursive(ll_node *current, ll_node *prev)
{
    if (!current)
    {
        return prev;
    }

    ll_node *next = current->next;
    current->next = prev;
    
    return reverse_recursive(next, current);
}

void ll_node_clear(ll_node **node)
{
    free((*node)->value);
    (*node)->value = NULL;
    free((*node)->next);
    (*node)->next = NULL;
}

int ll_node_init(ll_node **node, const size_t size, const void *value)
{
    *node = malloc(sizeof(ll_node));

    if (!*node)
    {
        puts("Node init failed");
        return -1;
    }

    (*node)->value = malloc(size);
    if (!(*node)->value)
    {
        free(*node);
        *node = NULL;
        puts("Node init failed");
        return -1;
    }

    memcpy((*node)->value, value, size);
    (*node)->next = NULL;

    return 0;
}

ll_node *last(ll_node *head)
{
    ll_node *current = head;
    ll_node *n;

    while (current)
    {
        n = current;
        current = current->next;
    }

    return n;
}

int ll_node_value(ll_node *node, const size_t size, void *value)
{
    if (!node) return -1;

    memcpy(value, node->value, size);
    return 0;
}