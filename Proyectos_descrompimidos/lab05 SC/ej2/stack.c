#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

stack stack_empty (){
   return NULL;
 }

 stack stack_push(stack s, stack_elem e){
    stack new_stack;//Creo struct de stack auxiliar
    unsigned int length = stack_size(s);
    new_stack = calloc(length,sizeof(stack));//Alojo en la memoria dinamica el lugar para los elementos, el size y la capacidad
    if(s == NULL){ //Si la pila es vacia la inicializo

        new_stack -> size = 0; //El tamaño empieza en 0
        new_stack -> elems = calloc(new_stack -> size, sizeof(stack_elem)); //Alojo la memoria, primer argumento la cantidad de elementos que voy a alojar y segundo la cantidad de bits que ocupa ese elemento
        new_stack -> elems[new_stack -> size] = e; //Guardo el elemento al final del arreglo
        new_stack -> size = new_stack -> size + 1;
        new_stack -> capacity = 1; //Establezco una capacidad inicial de 1

    } else if (new_stack->size == new_stack->capacity) { //Si la pila llega a su capacidad maxima
        new_stack -> size = s -> size; //Copio el tamaño
        new_stack -> capacity = s -> capacity; //Copio la capacidad
        new_stack -> capacity = new_stack->capacity * 2; //Duplico la capacidad
        new_stack -> elems = realloc(new_stack->elems, new_stack->capacity * sizeof(stack_elem)); // "s->capacity*sizeof(stack_elem)" alojo en la memoria la capacidad de la pila por la cantidad de bits de cada elemento 
        new_stack -> elems[new_stack -> size % new_stack -> capacity] = e; //Guardo el elemento al final del arreglo
        new_stack -> size = new_stack -> size + 1; //Aumento el tamaño de la pila
        assert(new_stack->elems != NULL); //Me aseguro de tener elementos en la pila ya que supuestamente llegue al tope de mi capacidad

    } else { //Si no llegue a la capacidad maxima, ni la pila es vacia
        new_stack -> size = s -> size; //Copio el tamaño
        new_stack -> capacity = s -> capacity; //Copio la capacidad
        new_stack -> elems[(new_stack -> size) % new_stack -> capacity] = e; //Agrego el elemento
        new_stack -> size = new_stack -> size + 1; //Aumento el tamaño de la pila
    }
    s = new_stack;
    return s;
 }

 // size es mi posicion final, es decir el largo del arreglo (i + k) % size
 // quiero dar un paso atras por tanto (i - 1) % size
 // i es mi posicion iniciar, y arranco del final (size - 1) % size
 // por ej, mi size es 4, (4 - 1) % 4 = 3 % 4 = 1, coloca el elemento en la posicion 1 [0,4,3,2,1]
 // 0 [1] 1 [2,1] 2 [3,2,1] 3 [4,3,2,1] 4 [5,4,3,2,1]
 // pos = 0 
 
 stack stack_pop(stack s){  
    assert(!stack_is_empty(s));
    s -> size = s -> size - 1;
    return s;
 }


 unsigned int stack_size(stack s) {
    unsigned int n;
    if(s == NULL){
        return 0;
    } else{
    n = s -> size;
    }
    return n;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    stack_elem e_pop;
    e_pop = s -> elems[s->size];
    return e_pop;
}

bool stack_is_empty (stack s){
  return (s == NULL);
}

stack_elem *stack_to_array(stack s){
    stack_elem* array; 
    array = s->elems;
    return array;
}

stack stack_destroy (stack s){
  if (s != NULL) {
        free(s->elems);
        s->elems = NULL;
        free(s);
        s = NULL;
    }
  return s;
}

