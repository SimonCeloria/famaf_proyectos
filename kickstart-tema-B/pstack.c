#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node *front;
};

struct s_node {
    pstack_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};


static float calculate_priority(float average_grade,
                                unsigned int approved_courses)
{
    float priority = 0;
    priority = 0.3 * (average_grade/MAX_GRADE) + 0.7 * (approved_courses/TOTAL_COURSES);
    return priority;
}

static struct s_node *create_node(pstack_elem e,
                                  float average_grade,
                                  unsigned int approved_courses)
{
    struct s_node *new_node = NULL;
    float priority = calculate_priority(average_grade, approved_courses);
    new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node -> approved_courses = approved_courses;
    new_node -> average_grade = average_grade;
    new_node -> elem = e;
    new_node -> next = NULL;
    new_node -> priority = priority;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    free(node);
    node=NULL;
    assert(node == NULL);
    return node;
}

bool is_valid(pstack s)
{
    bool is_ord = true;
    struct s_node *index = s -> front;
    if (s == NULL)
    {
        is_ord = true;
    } else {
        while ((index != NULL) && (index -> next != NULL) && is_ord)
        {
            is_ord &= (index -> priority >= (index -> next)-> priority);
            index = index -> next;
        }
        
    }
    return is_ord;
}

static bool invrep(pstack s)
{
    bool is_pstack = s != NULL ? is_valid(s) : true;
    return is_pstack;
}

pstack pstack_empty(void)
{
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    if (s == NULL)
    {
        printf("Memory allocate error");
        exit(EXIT_FAILURE);
    }
    
    s -> size = 0;
    return s;
}

pstack pstack_push(pstack s,
                   pstack_elem e,
                   float average_grade,
                   unsigned int approved_courses)
{
    assert(invrep(s));
    struct s_node *new_node = create_node(e, average_grade, approved_courses);
    struct s_node *index = s -> front;
    struct s_node *parent = NULL;
    bool flag = true;
    float priority = calculate_priority(average_grade, approved_courses);
    if (index == NULL)
    {
        s -> front = new_node;
    } else {
        while (flag && index -> priority > priority) //Si la prioridad es menor, busco un nodo con menor prioridad y lo coloco justo despues
        {
            parent = index; //Guardo el puntero al nodo anterior
            index = index -> next; //Muevo el indice
            if (index == NULL) //Si llego al final corto el while
            {
                flag = false;
            }
        }
        new_node -> next = index;
        if (parent != NULL)
        {
            parent -> next = new_node;
        } else { //Si todas las prioridades son iguales, nunca ejecuta el while y se comporta como stack
            s -> front = new_node;
        }
        

    }
    s -> size += 1;
    assert(invrep(s) && s->front != NULL); 
    return s;
}

bool pstack_is_empty(pstack s) 
{
    return (s == NULL || s -> size == 0);
}

pstack_elem pstack_top(pstack s) 
{
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->elem;
}

float pstack_top_average_grade(pstack s) 
{
    assert(invrep(s) && !pstack_is_empty(s));
    float top_average_grade = (s -> front) -> average_grade;
    return top_average_grade;
}

unsigned int pstack_top_approved_courses(pstack s) 
{
    assert(invrep(s) && !pstack_is_empty(s));
    float top_approved_courses = (s -> front) -> approved_courses;
    return top_approved_courses;
}

float pstack_top_priority(pstack s) 
{
    assert(invrep(s) && !pstack_is_empty(s));
    float top_priority = (s -> front) -> priority;
    return top_priority;
}

unsigned int pstack_size(pstack s) 
{
    assert(invrep(s));
    unsigned int size=0;
    if (s != NULL)
    {
        size = s -> size;
    }
    
    return size;
}

pstack pstack_copy(pstack s)
{
    assert(invrep(s));
    if (s == NULL) //SI es null no hago nada
    {
        return NULL;
    }
    
    struct s_pstack *cp_s = NULL; //Creo un puntero a mi stack
    cp_s = malloc(sizeof(struct s_pstack)); //Alojo mi memoria para el stack
    cp_s -> size = s -> size; //Copio los elementos del stack
    cp_s -> front = s -> front; 
    struct s_node *index = NULL; //Creo el puntero que utilizo de indice
    index = (s -> front) -> next;//Hago que apunte al segundo nodo del stack original

    while(index != NULL){ //Voy nodo por nodo, creando un nuevo stack a partir del original utilizando el index a partir del primer nodo del stack original
       cp_s = pstack_push(cp_s,index -> elem, index -> average_grade, index -> approved_courses);
       index = index -> next;    
    }

    return cp_s;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s));
    struct s_node * node = s -> front;
    s -> front = s -> front -> next;
    s -> size -= 1;
    node = destroy_node(node);
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) 
{

    while (s -> front != NULL) {
        s = pstack_pop(s);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}
