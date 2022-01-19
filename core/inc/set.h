#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct set_node
{
    const char *key;
    size_t len;
    struct set_node *next;
}
set_node;

typedef struct set
{
    set_node **nodes;
    size_t count;
}
set;

size_t hash(const char *key);

int set_init(set *set, const size_t count);

int set_insert(set *set, const char *key);

int set_insert_node(set *set, set_node *node);

int set_remove(set *set, const char *key);

int set_remove_node(set *set, set_node *node);

int set_node_init(set_node **node, const char *key);

int set_node_check(set_node *head, const char *key);

set_node *last_set_node(set_node *head);

void set_node_clear(set_node **node);