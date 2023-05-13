#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
typedef int stack_elem;

typedef struct _s_stack {
  struct _node * next;
  stack_elem elem;
};


 stack stack_empty (){
   return NULL;
 }

 stack stack_push(stack s, stack_elem e){
    s -> elem = e;
    return s;
 }

 stack stack_pop(stack s){
    s = s -> next;
    return s;
 }

 unsigned int stack_size(stack s){
    unsigned int length;
    stack copy_stack;
    
    length = 0u;
    copy_stack = s;
    while(!stack_is_empty(copy_stack)){
        length = length + 1;
        copy_stack = copy_stack -> next;
    }
    return length;
 }

stack_elem stack_top(stack s){
    assert(stack_is_empty(s));
    stack_elem e_pop;
    e_pop = s -> elem;
    return e_pop;
}

bool stack_is_empty (stack s){
  return (s = NULL);
}

stack_elem *stack_to_array(stack s){
    //Tengo que crear el arreglo de forma dinamica
    unsigned int length;
    length = stack_size(s);
    first = calloc(sizeof());
}

stack stack_destroy (stack s){
  if(!stack_is_empty(s)){
    stack_destroy(s->next);
    free(s);
  }
  return s;
}

