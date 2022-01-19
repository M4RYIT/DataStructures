#include <stdio.h>
#include <string.h>
#include "dictionary.h"

int dict_init(dict *dict, const size_t count, const size_t t)
{
    dict->nodes = calloc(count, sizeof(dict_node*));
    if (!dict->nodes)
    {
        puts("Dictionary init failed");
        return -1;
    }

    dict->count = count;
    dict->type = t;
    dict->collisions = 0;

    return 0;
}

dict_node *dict_by_key(dict *dict, const char* key)
{
    size_t index = dict_hash(key) % dict->count;

    dict_node *n = dict_node_check(dict->nodes[index], key);

    if (!n)
    {
        puts("Key not found");
    }

    return n;
}

dict_node *dict_by_value(dict *dict, const void *value)
{
    dict_node *n = NULL;

    for (size_t i=0; i<dict->count; i++)
    {
        n = dict_node_value_check(dict->nodes[i], dict->type, value);

        if (n) break;
    }

    if (!n)
    {
        puts("Value not found");
    }

    return n;
}

void dict_clear(dict *dict)
{
    for (size_t i=0; i<dict->count; i++)
    {
        dict_node **head = &dict->nodes[i];
        dict_node *n;

        while(*head)
        {
            n = (*head)->next;
            dict_node_clear(head);
            *head = n;
        }
    }

    dict->nodes = NULL;
    dict->count = 0;
    dict->collisions = 0;
    dict->type = 0;
}

void dict_resize(dict **d)
{
    dict *new_dict = malloc(sizeof(dict));
    dict_init(new_dict, (*d)->count + count_inc, (*d)->type);   

    for (size_t i=0; i<(*d)->count; i++)
    {      
        dict_node *n = (*d)->nodes[i];

        while(n)
        {
            dict_add(new_dict, n->key, n->value);
            n = n->next;
        }
    }

    dict_clear(*d);
    *(*d) = *new_dict;

    puts("Dictionary resized");
}

int dict_add(dict *dic, const char *key, const void *value)
{
    if (dic->collisions>=max_collisions)
    {
        dict_resize(&dic);
    }

    size_t index = dict_hash(key) % dic->count;

    dict_node **head = &dic->nodes[index];

    if (!*head)
    {
        return dict_node_init(head, key, dic->type, value);
    }

    if (!dict_node_check(*head, key))
    {        
        if (dict_node_init(&last_dict_node(*head)->next, key, dic->type, value)) return -1;
        dic->collisions++;
        return 0;
    }

    puts("Key already exist");
    return -1;
}

int dict_remove(dict *dict, const char *key)
{
    size_t index = dict_hash(key) % dict->count;

    dict_node *head = dict->nodes[index];

    if (!head)
    {
        puts("Key not found");
        return -1;
    }

    dict_node *n = head->next;

    if (!strcmp(head->key, key))
    {
        if (n) dict->collisions--;
        dict_node_clear(&head);
        dict->nodes[index] = n;
        return 0;
    }

    while(n)
    {
        if (!strcmp(n->key, key))
        {
            head->next = n->next;
            dict_node_clear(&n);
            dict->collisions--;
            return 0;
        }

        head = n;
        n = n->next;
    }

    puts("Key not found");
    return -1;
}

int dict_node_init(dict_node **node, const char *key, const size_t size, const void* value)
{
    *node = malloc(sizeof(dict_node));
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

    (*node)->key = key;
    (*node)->next = NULL;

    return 0;
}

void dict_node_clear(dict_node **node)
{
    free((*node)->value);
    (*node)->value = NULL;
    free((*node)->next);
    (*node)->next = NULL;
    (*node)->key = NULL;
}

dict_node *last_dict_node(dict_node *head)
{
    dict_node *current = head;
    dict_node *n;

    while(current)
    {
        n = current;
        current = current->next;
    }

    return n;
}

dict_node *dict_node_check(dict_node* head, const char* key)
{
    dict_node *n = head;

    while(n)
    {
        if (!strcmp(n->key, key))
        {
            return n;
        }

        n = n->next;
    }

    return n;
}

dict_node *dict_node_value_check(dict_node *head, const size_t size, const void *value)
{
    dict_node *n = head;

    while (n)
    {
        if (!memcmp(n->value, value, size))
        {
            return n;
        }

        n = n->next;
    }

    return n;
}

int dict_node_value(dict_node *node, const size_t size, void *value)
{
    if (!node)
    {
        return -1;
    }

    memcpy(value, node->value, size);
    return 0;
}

void set_dict_node(dict_node *node, const size_t size, void *value)
{
    memcpy(node->value, value, size);
}

size_t dict_hash(const char *key)
{
    size_t hash = 5381;
    size_t len = strlen(key);

    for (size_t i=0; i<len; i++)
    {
        hash = ((hash<<5) + hash) ^ key[i];
    }

    return hash;
}