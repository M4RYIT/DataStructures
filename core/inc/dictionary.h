#pragma once

#include <stdlib.h>
#include <stdint.h>

static const size_t max_collisions = 3;
static const size_t count_inc = 3;

typedef struct dict_node
{
    const char* key;
    uint8_t *value;
    struct dict_node *next;
}
dict_node;

typedef struct dict
{
    dict_node **nodes;
    size_t count;
    size_t type;
    size_t collisions;
}
dict;

int dict_init(dict *dict, const size_t count, const size_t t);

dict_node *dict_by_key(dict *dict, const char* key);

dict_node *dict_by_value(dict *dict, const void *value);

void dict_clear(dict *dict);

void dict_resize(dict **dict);

int dict_add(dict *dict, const char *key, const void *value);

int dict_remove(dict *dict, const char *key);

int dict_node_init(dict_node **node, const char *key, const size_t size, const void* value);

void dict_node_clear(dict_node **node);

dict_node *dict_node_check(dict_node* head, const char* key);

dict_node *last_dict_node(dict_node *head);

int dict_node_value(dict_node *node, const size_t size, void *value);

dict_node *dict_node_value_check(dict_node *head, const size_t size, const void *value);

void set_dict_node(dict_node *node, const size_t size, void *value);

size_t dict_hash(const char *key);