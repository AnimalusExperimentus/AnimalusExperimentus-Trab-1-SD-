#ifndef _LIST_PRIVATE_H
#define _LIST_PRIVATE_H

#include "list.h"

struct node_t {
    struct entry_t* entry;
    struct node_t* next;
    

};

struct list_t {
    struct node_t* head;

};

void list_destroy_aux(struct node_t *head);

void list_add_aux(struct node_t *node,struct entry_t *entry);

struct entry_t *list_get_aux(struct node_t *node, char *key);

int list_size_aux(struct node_t *node);



void list_print(struct list_t* list);

#endif
