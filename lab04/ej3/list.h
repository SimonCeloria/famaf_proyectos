#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

/* counter as a pointer to structs to guarantee encapsulation */
typedef struct _node * list ;

typedef struct _node _node;

typedef int list_elem;

/* Constructors */
list empty_list(void);
/*
    Create a empty list with a empty list. Allocates new memory.
    Being list the returned list, list_is_init(c) should be true.
*/

list addl(list l,list_elem e);
/*
    Adds an elemt to the list.
*/


/* Operations */
bool is_empty(list l);
/*
    Return true if list l is empty.
*/

list_elem head(list l);
/*
    Returns the first element of the list.
    PRECONDITION: !is_empty(l)
*/

list tail(list l);
/*
    Delete the first element of the list.
    PRECONDITION: !is_empty(l)
*/

list addr(list_elem e, list l);
/*
    Adds an elemt at the end of the list.
*/

int length(list l);
/*
    Returns the lenght of the list.
*/

list concat(list l1, list l2);
/*
    Concatenates list 1 with list 2 and returns l1.
*/

list_elem index(list l,int n);
/*
    Returns the element in the position n of the list.
    PRECONDITION: lenght(l) > n 
*/

list take(list l, int n);
/*
    Keep only the first n elements in l, removing the rest.
    PRECONDITION: !is_empty(l)
*/

list drop(list l, int n);
/*
    Drops the n elements in l, keeping the rest.
    PRECONDITION: !is_empty(l)
*/

list copy(list l1);
/*
    Copy all the elements of the list.
*/

void destroy_list(list l);
/*
   Frees memory for l.
*/

#endif