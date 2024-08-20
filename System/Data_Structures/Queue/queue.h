#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "../../Libraries/standard_libraries.h"

typedef int entry_type;

typedef struct node
{
    entry_type entry;
    struct node *next;
}node;

typedef struct queue
{
    node *front;
    node *rear;
    int size;
}queue;

void create_queue (queue *pq);
int is_queue_empty (queue *pq);
int is_queue_full (queue *pq);
void enqueue (entry_type entry,queue *pq);
void dequeu (entry_type *pe,queue *pq);
int queue_size (queue *pq);
void clear_queue (queue *pq);
void traverse_queue (queue *pq,void(*pf)(entry_type));

#endif // QUEUE_H_INCLUDED
