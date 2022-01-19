#include <stdio.h>
#include <string.h>
#include "dblinklist.h"

void dllist_init(dllist *list, const size_t t)
{
    list->type = t;
    list->head = NULL;
}

size_t dllist_count(dllist *list)
{
    size_t count = 0;
    dll_node *n = list->head;

    while(n)
    {
        count++;
        n = n->next;
    }

    return count;
}

void dllist_shuffle(dllist *list)
{
    size_t count = dllist_count(list);
    size_t j;
    void *temp;    
    dll_node *node_1;
    dll_node *node_2;

    for (size_t i=0; i<count-2; i++)
    {
        j = random_range(i, count);
        node_1 = dll_node_by_index(list, i);
        node_2 = dll_node_by_index(list, j);
        temp = node_1->value;
        node_1->value = node_2->value;
        node_2->value = temp;
    }
}

int dllist_append_value(dllist *list, const void *value)
{
    if (!list->head)
    {
        return dll_node_init(&list->head, NULL, list->type, value);        
    }

    dll_node *tail = last_dll_node(list->head);
    return dll_node_init(&tail->next, tail, list->type, value);
}

int dllist_append_node(dllist *list, dll_node *node)
{
    if (!list->head)
    {
        list->head = node;
        return 0;
    }

    dll_node *tail = last_dll_node(list->head);
    tail->next = node;
    node->prev = tail;
    
    return 0;
}

int dllist_remove_node(dllist *list, dll_node *node)
{
    if (!list->head || !node)
    {
        puts("Empty list or null node");
        return -1;
    }

    dll_node *current = list->head;
    if (current==node)
    {
        list->head = current->next;
        list->head->prev = NULL;
        current->next = NULL; 
        return 0;
    }

    dll_node *n = current->next;
    while(n)
    {
        if (n==node)
        {
            current->next = n->next;
            n->next->prev = current;
            n->prev = NULL;
            n->next = NULL;
            return 0;
        }

        current = n;
        n = current->next;
    }

    puts("Node not found");
    return -1;
}

int dllist_insert_after(dllist *list, dll_node *parent, dll_node *child)
{
    if (!list->head || !parent || !child)
    {
        puts("Empty list or null node");
        return -1;
    }

    if (last_dll_node(list->head)==parent)
    {
        return dllist_append_node(list, child);        
    }

    dll_node *current = list->head;
    while(current)
    {
        if (current==parent)
        {
            child->prev = current;
            child->next = current->next;
            current->next = child;
            child->next->prev = child;
            return 0;
        }

        current = current->next;
    }

    puts("Node not found");
    return -1;
}

int dllist_insert_before(dllist *list, dll_node *parent, dll_node *child)
{
    if (!list->head || !parent || !child)
    {
        puts("Empty list or null node");
        return -1;
    }

    if (list->head==child)
    {
        list->head = parent;
        parent->next = child;
        child->prev = parent;
        return 0;
    }

    dll_node *current = list->head->next;
    while(current)
    {
        if (current==child)
        {
            parent->next = current;
            parent->prev = current->prev;
            current->prev->next = parent;
            current->prev = parent;
            return 0;
        }

        current = current->next;
    }

    puts("Node not found");
    return -1;
}

int dll_node_init(dll_node **node, dll_node *parent, const size_t size, const void *value)
{
    *node = malloc(sizeof(dll_node));

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
    (*node)->prev = parent;
    (*node)->next = NULL;    

    return 0;
}

dll_node *dll_node_by_index(dllist *list, const size_t index)
{
    size_t count = dllist_count(list);

    if (index>=count)
    {
        puts("Invalid index");
        return NULL;
    }

    dll_node *n = list->head;

    for (size_t i=0; i<index; i++)
    {
        n = n->next;
    }

    return n;
}

dll_node *last_dll_node(dll_node *head)
{
    dll_node *current = head;
    dll_node *n;

    while (current)
    {
        n = current;
        current = current->next;
    }

    return n;
}

int dll_node_value(dll_node *node, const size_t size, void *value)
{
    if (!node) return -1;

    memcpy(value, node->value, size);
    return 0;
}

size_t random_range(const size_t min, const size_t max)
{   
    return (size_t)rand() % (max-min) + min;
}