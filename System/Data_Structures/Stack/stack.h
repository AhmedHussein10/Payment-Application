#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "../../Libraries/standard_libraries.h"

typedef int entry_type;

typedef struct node
{

    entry_type entry;
    struct node *next;

}node;

typedef struct stack
{

    node *top;
    int size;

}stack;


void create_stack (stack *ps);
int is_stack_empty (stack *ps);
int is_stack_full (stack *ps);
void push (entry_type entry,stack *ps);
void pop (entry_type *pe,stack *ps);
void clear_stack (stack *ps);
int stack_size (stack *ps);
void traverse_stack (stack *ps,void (*pf)(entry_type));

#endif // STACK_H_INCLUDED
