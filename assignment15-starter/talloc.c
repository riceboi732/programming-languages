/*
talloc.c
Written by Victor Huang and Thien K. M. Bui
Last editted 02-13-2022
*/

#include <stdlib.h>
#include <assert.h>

#include "value.h"
#include "talloc.h"

// store head of talloc list
Value *head_talloc = NULL;

// talloc()

// Replacement for malloc that stores the pointers allocated. It should store
// the pointers in a linked list, and you have license here to duplicate code
// that you wrote for linkedlist.c. To be clear, don't actually call functions
// that are defined in linkedlist.h, because then you'll end up with circular
// dependencies, since you'll be using talloc in linkedlist.c.

// insert at the head since order does not matter
void *talloc(size_t size)
{
    // make new PTR Value
    Value *new_ptr = malloc(sizeof(Value));
    new_ptr->type = PTR_TYPE;
    new_ptr->p = malloc(size);

    // make new CONS (act as linked nodes) car will be the new head, and cdr will be the previous head
    Value *new_cons = malloc(sizeof(Value));
    new_cons->type = CONS_TYPE;

    // cdr here will point to a NULL_TYPE
    if (head_talloc == NULL)
    {
        Value *null_value = malloc(sizeof(Value));
        null_value->type = NULL_TYPE;

        new_cons->c.car = new_ptr;
        new_cons->c.cdr = null_value;
        head_talloc = new_cons;
        return new_ptr->p;
    }
    else
    {
        // make new PTR type
        new_cons->c.car = new_ptr;
        new_cons->c.cdr = head_talloc;
        head_talloc = new_cons;
        return new_ptr->p;
    }
}

// helper function to make freeing all associated memories of talloc easy
void cleanup(Value *head)
{
    if (head->type == NULL_TYPE)
    {
        free(head);
    }
    else if (head->type == PTR_TYPE)
    {
        free(head->p);
        free(head);
    }
    else
    {
        cleanup(head->c.car);
        cleanup(head->c.cdr);
        free(head);
    }
}

// Free all pointers allocated by talloc, as well as whatever memory you
// allocated for purposes of maintaining the active list. Hint: consider
// that talloc may be called again after tfree is called...
void tfree()
{
    Value *current = head_talloc;

    cleanup(current);

    head_talloc = NULL;
}

// Replacement for the C function 'exit' that consists of two lines: it calls
// tfree before calling exit. It's useful to have later on, since you'll be able
// to call it to clean up memory and exit your program whenever an error occurs.
// Briefly look up exit to get a sense of what the 'status' parameter does.
void texit(int status)
{
    tfree();
    exit(status);
}