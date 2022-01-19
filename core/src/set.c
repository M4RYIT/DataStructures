#include <stdio.h>
#include <string.h>
#include "set.h"

int set_init(set *set, const size_t count)
{
    set->nodes = calloc(count, sizeof(set_node*));
    if (!set->nodes)
    {
        puts("Set init failed");
        return -1;
    }

    set->count = count;
    return 0;
}

int set_insert(set *set, const char *key)
{
    size_t index = hash(key) % set->count;

    set_node **head = &set->nodes[index];

    if (!*head)
    {
        return set_node_init(head, key);
    }

    if (!set_node_check(*head, key))
    {
        set_node *tail = last_set_node(*head);
        return set_node_init(&tail->next, key);
    }

    puts("Insert failed");
    return -1;
}

int set_remove(set *set, const char *key)
{
    size_t index = hash(key) % set->count;

    set_node *head = set->nodes[index];
    
    if (!head)
    {
        puts("Empty");
        return -1;
    }

    set_node *n = head->next;

    if (!strcmp(head->key, key))
    {
        set_node_clear(&head);
        set->nodes[index] = n;
        return 0;
    }
    
    while(n)
    {        
        if (!strcmp(n->key, key))
        {
            head->next = n->next;
            set_node_clear(&n);
            return 0;
        }

        head = n;
        n = n->next;
    }

    puts("Key not found");
    return -1;
}

int set_insert_node(set *set, set_node *node)
{
    size_t index = hash(node->key) % set->count;

    set_node **head = &set->nodes[index];

    if (!*head)
    {
        *head = node;
        return 0;
    }

    if (!set_node_check(*head, node->key))
    {
        set_node *tail = last_set_node(*head);
        tail->next = node;
        return 0;
    }

    puts("Insert failed");
    return -1;
}

int set_remove_node(set *set, set_node *node)
{
    size_t index = hash(node->key) % set->count;

    set_node *head = set->nodes[index];

    if (!head)
    {
        puts("Empty");
        return -1;
    }

    set_node *n = head->next;

    if (head==node)
    {
        node->next = NULL;
        set->nodes[index] = n;
        return 0;
    }

    while(n)
    {
        if (n==node)
        {
            head->next = n->next;
            n->next = NULL;
            return 0;
        }

        head = n;
        n = n->next;
    }

    puts("Node not found");
    return -1;
}

void set_node_clear(set_node **node)
{    
    (*node)->key = NULL;
    (*node)->len = 0;
    free((*node)->next);
    (*node)->next = NULL;
}

int set_node_init(set_node **node, const char *key)
{
    *node = malloc(sizeof(set_node));
    
    if (!*node)
    {
        puts("Node init failed");
        return -1;
    }

    (*node)->key = key;
    (*node)->len = strlen(key);
    (*node)->next = NULL;

    return 0;
}

int set_node_check(set_node *head, const char *key)
{
    set_node *current = head;
    size_t len = strlen(key);

    while(current)
    {
        if (current->len==len && !strcmp(current->key, key))
        {
            puts("Key already exists");
            return -1;
        }

        current = current->next;
    }

    return 0;
}

set_node *last_set_node(set_node *head)
{
    set_node *current = head;
    set_node *n;

    while(current)
    {
        n = current;
        current = current->next;
    }

    return n;
}

size_t hash(const char *key)
{
    size_t hash = 5381;
    size_t len = strlen(key);

    for (size_t i=0; i<len; i++)
    {
        hash = ((hash<<5) + hash) ^ key[i];
    }

    return hash;
}