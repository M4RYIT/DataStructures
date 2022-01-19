#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct ll_node
{
    struct ll_node *next;
    void *value;
}
ll_node;

typedef struct llist
{
    ll_node *head;
    size_t type;    
}
llist;

void llist_init(llist *list, const size_t t);

int llist_append_value(llist *list, const void *value);

int llist_append_node(llist *list, ll_node *node);

int llist_remove_node(llist *list, ll_node *node);

int llist_pop(llist *list);

void llist_reverse_iterative(llist *list);

void llist_reverse_recursive(llist *list);

ll_node *reverse_recursive(ll_node *current, ll_node *prev);

int ll_node_init(ll_node **node, const size_t size, const void *value);

void ll_node_clear(ll_node **node);

ll_node *last(ll_node *head);

ll_node *last_ll_node(ll_node *head);

int ll_node_value(ll_node *node, const size_t size, void *value);