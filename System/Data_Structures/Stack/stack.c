#include "../../Libraries/standard_libraries.h"
#include "stack.h"

void create_stack (stack *ps)
{
    if (ps)
    {
        ps->top=NULL;
        ps->size=0;
    }
    else
        printf ("Out of memory \n");
}

int is_stack_empty (stack *ps)
{
    if (ps)
    {
        return ps->top==NULL;
    }
    else
        printf ("Out of memory \n");
}

int is_stack_full (stack *ps)
{
    if (ps)
    {
        return 0;
    }
    else
        printf ("Out of memory \n");
}

void push (entry_type entry,stack *ps)
{
    if (ps)
    {
        node *pn=(node*) malloc(sizeof (node));
        if (pn)
        {
            pn->entry=entry;
            pn->next=ps->top;
            ps->top=pn;
            ps->size++;
        }
        else
            printf ("Out of memory \n");
    }
    else
        printf ("Out of memory \n");
}

void pop (entry_type *pe,stack *ps)
{
    if (ps)
    {
        *pe=ps->top->entry;
        node *pn=ps->top;
        ps->top=pn->next;
        free (pn);
        ps->size--;
    }
    else
        printf ("Out of memory \n");
}

int stack_size (stack *ps)
{
    if (ps)
    {
        return ps->size;
    }
    else
        printf ("Out of memory \n");
}

void clear_stack (stack *ps)
{
    if (ps)
    {
        node *pn=ps->top;
        while (pn)
        {
            pn=pn->next;
            free (ps->top);
            ps->top=pn;
        }
        ps->size=0;
    }
    else
        printf ("Out of memory \n");
}

void traverse_stack (stack *ps,void (*pf)(entry_type))
{
    if (ps)
    {
        node *pn=ps->top;
        while (pn)
        {
            (*pf)(pn->entry);
            pn=pn->next;
        }
    }
    else
        printf ("Out of memory \n");
}
