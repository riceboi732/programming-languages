/*
linkedlist.c
Written by Victor Huang and Thien K. M. Bui
Last modified 02/12/22
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "linkedlist.h"
#include "talloc.h"
// Create a pointer to a new NULL_TYPE Value (hint: where in memory will
// the Value have to live?)
Value *makeNull()
{
    Value *new_null = talloc(sizeof(Value));
    new_null->type = NULL_TYPE;

    return new_null;
}

// Return whether the given pointer points at a NULL_TYPE Value. Use assertions
// to make sure that this is a legitimate operation. See the assignment
// instructions for further explanation on assertions.
bool isNull(Value *value)
{
    if (value->type == NULL_TYPE)
    {
        return true;
    }
    return false;
}

// Create a pointer to a new CONS_TYPE Value
Value *cons(Value *newCar, Value *newCdr)
{
    Value *new_value = talloc(sizeof(Value));
    new_value->type = CONS_TYPE;

    struct ConsCell new_cons_cell;
    new_cons_cell.car = newCar;
    new_cons_cell.cdr = newCdr;

    new_value->c = new_cons_cell;
    return new_value;
}

// Return a pointer to the car value for the cons cell at the head of the given
// linked list. Use assertions here to make sure that this is a legitimate operation
// (e.g., there is no car value at the head of an empty list). See the assignment
// instructions for further explanation.
Value *car(Value *list)
{
    // if not empty
    if (list->type == CONS_TYPE)
    {
        return list->c.car;
    }
    else if (list->type == NULL_TYPE)
    {
        return list;
    }
    // error, should never be of type int/null here
    else
    {
        assert(false != true && "Incorrect type, something went wrong --kb");
        return list;
    }
}

// Return a pointer to the cdr value for the cons cell at the head of the given linked
// list. Again use assertions to make sure that this is a legitimate operation.
Value *cdr(Value *list)
{
    // if not empty
    if (list->type == CONS_TYPE)
    {
        return list->c.cdr;
    }
    else
    {
        assert(false != true && "invalid operation on empty list --kb");
        return list;
    }
}

// Display the contents of the linked list to the screen in the
// format of a Scheme list -- e.g., ( 33 "lol" 9.9 ). It's okay
// to just use printf here, though you'll have to add the quotes in
// yourself, for strings.
void display(Value *list)
{
    bool at_end = false;
    Value *current_value = list;

    printf("( ");
    while (!at_end)
    {

        if (current_value->type == CONS_TYPE)
        {
            // copy over whatever addresses are in the current ConsCell, it'll get deleted anyway so it doesn't matter
            struct ConsCell printed_value = current_value->c;
            // check the type of the car cell (Value typed pointer)
            switch (printed_value.car->type)
            {
            case INT_TYPE:
                printf("%i ", printed_value.car->i);
                break;
            case DOUBLE_TYPE:
                printf("%f ", printed_value.car->d);
                break;
            case STR_TYPE:
                printf("\"%s\" ", printed_value.car->s);
                break;
            default:
                printf("%i", printed_value.car->i);
            }

            current_value = cdr(current_value);
        }
        else
        {
            printf(")\n");
            at_end = true;
        }
    }
}

// Return a new list that is the reverse of the one that is passed in. None of
// the values in the original linked list should be copied this time. Instead,
// create a new linked list of CONS_TYPE nodes whose car values point to the
// corresponding car values in the original list.
Value *reverse(Value *list)
{
    // copy over the current values into heap
    Value *current = list;
    Value *reverse_list = makeNull();

    // at the last node of the list
    while (!isNull(current))
    {
        reverse_list = cons(car(current), reverse_list);
        current = cdr(current);
    }
    return reverse_list;
}

// Return the length of the given list, i.e., the number of cons cells.
// Use assertions to make sure that this is a legitimate operation.
int length(Value *value)
{

    int length = 0;
    Value *current = value;
    while (!isNull(current))
    {
        length = length + 1;
        current = cdr(current);
    }
    return length;
}