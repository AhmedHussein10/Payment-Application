#include "../../Libraries/standard_libraries.h"
#include "../../Libraries/platform_type.h"
#include "list.h"


int create_list (list *pl)
{
    if (pl==NULL)
        return -1;
    pl->head=NULL;
    pl->size=0;
    return 1;
}

int is_list_empty (list *pl)
{
    if (pl==NULL)
        return -1;
    return pl->size==0;
}

int is_list_full (list *pl)
{
    if (pl==NULL)
        return -1;
    return 0;
}

int insert_Account (int pos,void *Account,list *pl)
{
    if (pl==NULL)
        return -1;
    node *pn=(node*) malloc(sizeof(node));
    if (pn==NULL)
        return -1;
    pn->ptr=Account;
    if (pos==0)
    {
        pn->next=pl->head;
        pl->head=pn;
    }
    else
    {
        node *pq=pl->head;
        for (int i=0;i<pos-1;i++)
        {
            pq=pq->next;
        }
        pn->next=pq->next;
        pq->next=pn;
    }
    pl->size++;
    return 1;
}

int delete_Account (int pos,void *Account,list *pl)
{
    if (pl==NULL)
        return -1;
    node *pn=pl->head;
    if (pos==0)
    {
        Account=pn->ptr;
        pl->head=pn->next;
        free (pn);
    }
    else
    {
        for (int i=0;i<pos-1;i++)
        {
            pn=pn->next;
        }
        node *pq=pn->next;
        Account=pq->ptr;
        pn->next=pq->next;
        free (pq);
    }
    pl->size--;
    return 1;
}

int list_size (list *pl)
{
    if (pl==NULL)
        return -1;
    return pl->size;
}


int traverse_Accounts (list *pl,void (*pf) (void*))
{
    if (pl==NULL)
        return -1;
    node *pn=pl->head;
    while (pn)
    {
        (*pf) (pn->ptr);
        pn=pn->next;
    }
    return 1;
}


int clear_list (list *pl)
{
    if (pl==NULL)
        return -1;
    node *pn=pl->head;
    while (pl->head)
    {
        pn=pl->head->next;
        free (pl->head);
        pl->head=pn;
    }
    pl->size=0;
    return 1;
}

