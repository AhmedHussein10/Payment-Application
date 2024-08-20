#include "../../Libraries/standard_libraries.h"
#include "queue.h"

void create_queue (queue *pq)
{
    if (pq)
    {
        pq->front=NULL;
        pq->rear=NULL;
        pq->size=0;
    }
    else
        printf ("Out of memory \n");
}

int is_queue_empty (queue *pq)
{
    if (pq)
    {
        return pq->front==NULL;
    }
    else
        printf ("Out of memory \n");
}

int is_queue_full (queue *pq)
{
    return 0;
}

void enqueue (entry_type entry,queue *pq)
{
    if (pq)
    {
        node *pn=(node*)malloc(sizeof(node));
        if (pn)
        {
            pn->entry=entry;
            pn->next=NULL;
            if (!pq->rear)
            {
                pq->rear=pn;
            }
            else
            {
                pq->rear->next=pn;
            }
            pq->rear=pn;
            pq->size++;
        }
        else
            printf ("Out of memory \n");
    }
    else
        printf ("Out of memory \n");
}

void dequeu (entry_type *pe,queue *pq)
{
    if (pq)
    {
        node *pn=pq->front;
        *pe=pn->entry;
        pq->front=pn->next;
        free (pn);
        if (!pq->front)
        {
            pq->rear=NULL;
        }
        pq->size--;
    }
    else
        printf ("Out of memory \n");
}

int queue_size (queue *pq)
{
    if (pq)
    {
        return pq->size;
    }
    else
        printf ("Out of memory \n");
}

void clear_queue (queue *pq)
{
    if (pq)
    {
        while (pq->front)
        {
            pq->rear=pq->front->next;
            free (pq->front);
            pq->front=pq->rear;
        }
        pq->size=0;
    }
    else
        printf ("Out of memory \n");
}

void traverse_queue (queue *pq,void(*pf)(entry_type))
{
    if (pq)
    {
        for (node *pn=pq->front;pn;pn->next)
        {
            (*pf)(pn->entry);
        }
    }
    else
        printf ("Out of memory \n");
}
