#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct dll_node
{
    struct dll_node *prev;
    struct dll_node *next;
    void *value;
}
dll_node;

typedef struct dllist
{
    size_t type;
    dll_node *head;
}
dllist;

void dllist_init(dllist *list, const size_t t);

size_t dllist_count(dllist *list);

void dllist_shuffle(dllist *list);

int dllist_append_value(dllist *list, const void *value);

int dllist_append_node(dllist *list, dll_node *node);

int dllist_remove_node(dllist *list, dll_node *node);

int dllist_insert_after(dllist *list, dll_node *parent, dll_node *child);

int dllist_insert_before(dllist *list, dll_node *parent, dll_node *child);

int dll_node_init(dll_node **node, dll_node *parent, const size_t size, const void *value);

dll_node *dll_node_by_index(dllist *list, const size_t index);

dll_node *last_dll_node(dll_node *head);

int dll_node_value(dll_node *node, const size_t size, void *value);

size_t random_range(const size_t min, const size_t max);