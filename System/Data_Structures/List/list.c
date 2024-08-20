#include "../../Libraries/standard_libraries.h"
#include "list.h"

void create_list (list *pl)
{
    pl->head=NULL;
    pl->size=0;
}

int is_list_empty (list *pl)
{
    return pl->size==0;
}

int is_list_full (list *pl)
{
    return 0;
}

void insert_list (int pos,entry_type entry,list *pl)
{
    if (pl)
    {
        node *pn=(node*) malloc(sizeof(node));
        if (pn)
        {
            pn->entry=entry;
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
        }
        else
        {
            printf ("out of memory \n");
        }
    }
    else
    {
        printf ("out of memory \n");
    }
}

void delete_list (int pos,entry_type *pe,list *pl)
{
    if (pl)
    {
        node *pn=pl->head;
        if (pos==0)
        {
            *pe=pn->entry;
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
            *pe=pq->entry;
            pn->next=pq->next;
            free (pq);
        }
        pl->size--;
    }
    else
    {
        printf ("out of memory \n");
    }
}

int list_size (list *pl)
{
    return pl->size;
}

void retrieve_list (int pos,entry_type *pe,list *pl)
{
    if (pl)
    {
        node *pn=pl->head;
        for (int i=0;i<pos;i++)
        {
            pn=pn->next;
        }
        *pe=pn->entry;
    }
    else
    {
        printf ("out of memory \n");
    }
}

void replace_list (int pos,entry_type entry,list *pl)
{
    if (pl)
    {
        node *pn=pl->head;
        for (int i=0;i<pos;i++)
        {
            pn=pn->next;
        }
        pn->entry=entry;
    }
    else
    {
        printf ("out of memory \n");
    }
}

void traverse_list (list *pl,void (*pf) (entry_type))
{
    if (pl)
    {
        node *pn=pl->head;
        while (pn)
        {
            (*pf) (pn->entry);
            pn=pn->next;
        }
    }
}


void clear_list (list *pl)
{
    if (pl)
    {
        node *pn=pl->head;
        while (pl->head)
        {
            pn=pl->head->next;
            free (pl->head);
            pl->head=pn;
        }
        pl->size=0;
    }
}

void display (entry_type entry)
{
    printf ("%d  ",entry);
}

