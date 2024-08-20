#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "../../Libraries/standard_libraries.h"

typedef int entry_type;

typedef struct node
{
    entry_type entry;
    struct node *next;
}node;

typedef struct
{
    node *head;
    int size;
}list;

void create_list (list *pl);
int is_list_empty (list *pl);
int is_list_full (list *pl);
void insert_list (int pos,entry_type entry,list *pl);
void delete_list (int pos,entry_type *pe,list *pl);
int list_size (list *pl);
void retrieve_list (int pos,entry_type *pe,list *pl);
void replace_list (int pos,entry_type entyr,list *pl);
void traverse_list (list *pl,void (*pf) (entry_type));
void clear_list (list *pl);
void display (entry_type entry);

#endif // LIST_H_INCLUDED
