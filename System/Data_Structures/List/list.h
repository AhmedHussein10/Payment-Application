#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "../../Libraries/standard_libraries.h"


typedef struct node
{
    void *ptr;
    struct node *next;

}node;

typedef struct
{
    node *head;
    uint32_t size;

}list;

int create_list (list *pl);
int is_list_empty (list *pl);
int is_list_full (list *pl);
int insert_Account (int pos,void *Account,list *pl);
int delete_Account (int pos,void *Account,list *pl);
int list_size (list *pl);
int traverse_Accounts (list *pl,void (*pf) (void*));
int clear_list (list *pl);


#endif // LIST_H_INCLUDED
