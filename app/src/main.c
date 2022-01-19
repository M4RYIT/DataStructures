#include <stdlib.h>
#include <stdio.h>
#include "dynarray.h"
#include "linklist.h"
#include "dblinklist.h"
#include "set.h"
#include "dictionary.h"

void dynarray_ex()
{
    dynarray array;
    dynarray_init(&array, sizeof(int));
    
    int a = 100;
    int b = 200;
    int c = 300;

    dynarray_append(&array, &a);
    dynarray_append(&array, &b);
    dynarray_append(&array, &c);

    dynarray_remove(&array, 0);

    printf("Number of elements = %llu\n", dynarray_len(&array));

    for (size_t i=0; i<dynarray_len(&array); i++)
    {
        int value;

        if (!dynarray_get(&array, i, &value))
        {
            printf("Element[%llu] : %d\n", i, value);
        }
    }

    dynarray_clear(&array);
}

void linked_list_ex()
{
    llist list;
    llist_init(&list, sizeof(int));

    int a = 100;
    int b = 200;
    int c = 300;

    llist_append_value(&list, &a);
    llist_append_value(&list, &b);
    llist_append_value(&list, &c);

    llist_pop(&list);

    int d = 400;
    int e = 500;

    ll_node *node_1 = NULL;
    ll_node_init(&node_1, sizeof(int), &d);
    llist_append_node(&list, node_1);

    ll_node *node_2 = NULL;
    ll_node_init(&node_2, sizeof(int), &e);
    llist_append_node(&list, node_2);

    llist_remove_node(&list, node_1);

    //llist_reverse_iterative(&list);
    llist_reverse_recursive(&list);

    int val;
    ll_node *n = list.head;

    while(n)
    {
        ll_node_value(n, list.type, &val);
        printf("%d\n", val);
        n = n->next;
    }       
}

void double_linked_list_ex()
{
    dllist list;
    dllist_init(&list, sizeof(int));

    int a = 100;
    int b = 200;
    int c = 300;
    int d = 400;
    int e = 500;

    dllist_append_value(&list, &a);
    dllist_append_value(&list, &b);
    dllist_append_value(&list, &c);
    dllist_append_value(&list, &d);
    dllist_append_value(&list, &e);    

    dll_node *node_1;
    int f = 600;
    dll_node_init(&node_1, NULL, sizeof(int), &f);

    dll_node *node_2;
    int g = 700;
    dll_node_init(&node_2, NULL, sizeof(int), &g);

    dll_node *node_3;
    int h = 800;
    dll_node_init(&node_3, NULL, sizeof(int), &h);
    
    dllist_append_node(&list, node_2);    

    dllist_insert_after(&list, node_2, node_3);
    dllist_insert_before(&list, node_1, node_2);

    dllist_remove_node(&list, node_1);

    dllist_shuffle(&list);

    int val;
    dll_node *n = list.head; 

    printf("Count : %zu\n", dllist_count(&list));

    puts("Forward reading");
    while(n)
    {
        dll_node_value(n, list.type, &val);
        printf("%d\n", val);
        n = n->next;
    }   

    n = last_dll_node(list.head);

    puts("Backward reading");
    while(n)
    {
        dll_node_value(n, list.type, &val);
        printf("%d\n", val);
        n = n->prev;
    } 

    size_t index = 1;
    dll_node *n_by_index = dll_node_by_index(&list, index);
    dll_node_value(n_by_index, list.type, &val);
    printf("[%zu] = %d\n", index, val);
}

void set_ex()
{
    set set;
    set_init(&set, 6);

    char *a = "Hi";
    char *b = "Hello";
    char *c = "Ciao";

    set_insert(&set, a);
    set_insert(&set, b);
    set_insert(&set, c);

    set_insert(&set, "Hallo");
    set_insert(&set, "Hola");
    set_insert(&set, "Salut");  

    set_node *node_1;
    set_node_init(&node_1, "Ahoj");
    set_insert_node(&set, node_1);

    set_node *node_2;
    set_node_init(&node_2, "Hei");
    set_insert_node(&set, node_2);

    set_remove(&set, "Salut");
    set_remove(&set, c);

    set_remove_node(&set, node_1);

    set_node *n;
    for (size_t i=0; i<set.count; i++)
    {
        printf("[%zu] = ", i);

        n = set.nodes[i];
        while (n)
        {
            printf("%s ", n->key);
            n = n->next;
        }
        
        puts("");
    }
}

void dictionary_ex()
{
    dict dic;
    dict_init(&dic, 4, sizeof(int));

    int a = 100;
    int b = 200;
    int c = 300;
    int d = 400;
    int e = 500;
    int f = 600;
    int g = 700;
    int h = 800;

    dict_add(&dic, "A", &a);
    dict_add(&dic, "B", &b);
    dict_add(&dic, "C", &c);
    dict_add(&dic, "D", &d);
    dict_add(&dic, "E", &e);
    dict_add(&dic, "F", &f);
    dict_add(&dic, "G", &g);
    dict_add(&dic, "H", &h);

    dict_remove(&dic, "A");
    dict_remove(&dic, "C");
 
    dict_node *node_by_key = dict_by_key(&dic, "F");
    dict_node *node_by_value = dict_by_value(&dic, &f);    

    printf("Count : %zu\n", dic.count);
    printf("Collisions : %zu\n", dic.collisions);

    char *key;
    int value;
    dict_node *node;

    for (size_t i=0; i<dic.count; i++)
    {
        printf("[%zu] = ", i);
        node = dic.nodes[i];

        while(node)
        {
            dict_node_value(node, dic.type, &value);
            printf("%s:%d ", node->key, value);
            node = node->next;
        }

        puts("");
    }

    dict_clear(&dic);
}

int main()
{
    // dynarray_ex();

    // linked_list_ex();

    // double_linked_list_ex();

    // set_ex();

    dictionary_ex();
    
    return 0;
}