#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


// Revisar memory leaks, ver valgrid, buscar algoritmo if para revisar si libere mi memoria. compilar usando -ggdb3 para revisar donde esta el error en valgrid

#include "list.h"

typedef struct _node {
    struct _node * next;
    list_elem elem;
} Node_t;


list empty_list(void){
    return NULL;
}

list addl(list l, list_elem e){
    Node_t *new_node;
    new_node = (Node_t *) malloc(sizeof(Node_t));
    new_node -> elem = e;
    new_node -> next = l;
    l = new_node;
    if (new_node == NULL) {
       skip;
    } else {
    free(new_node);
    }
    return l;
}


bool is_empty(list l){
    bool b;
    b = (l == NULL);
    return b;
}

list_elem head(list l){
    assert(!is_empty(l));
    list_elem e;
    e = l -> elem;
    return e;
}

list tail(list l){
    assert(!is_empty(l));
    list aux;
    aux = l;
    l = l->next;
    free(aux);
    return l;
}

list addr(list_elem e, list l){
    Node_t *aux1;
    Node_t *aux2;
    aux1 = malloc(sizeof(Node_t));
    aux1 -> elem = e;
    aux1 -> next = NULL;
    if (!is_empty(l)) {
        aux2 = l;
        while(aux2 -> next != NULL){
            aux2 = aux2 -> next;
        }
        aux2 -> next = aux1;
    } else {
        l = aux1;
    }

    return l;
}

int length(list l){
    int n;
    Node_t *aux;
    n = 0;
    aux = l;
    while(aux != NULL){
        n = n + 1;
        aux = aux -> next;
    }
    return  n;
}

list concat(list l1, list l2){
    if(is_empty(l1)) {
        l1 = l2;
    } else {
        list_elem aux;
        aux = head(l1);
        l1 =tail(l1);
        l1 = concat(l1,l2);
        l1 = addl(l1,aux);
    }
    return l1;
}

list_elem index(list l,int n){
    assert(length(l) > n);
    list_elem e;
    list aux;
    aux = l;
    if((n == 0)){
        e = head(aux);
    } else {
        e = index(aux->next, n - 1);
    }
    return e;
}

list take(list l, int n){
    assert(!is_empty(l));
    if((n == 0)){
        destroy_list(l);
    } else if((n > 0) && (!is_empty(l))){
        list_elem e;
        e = head(l);
        l = tail(l);
        l = take(l,n-1);
        l = addl(l,e);
    }
    return l;
}

list drop(list l, int n){
    assert(!is_empty(l));
    if(n > 0){
        l = tail(l);
        l = drop(l,n-1);
    }
    return l;
}

list copy(list l){
    list new_list;
    if(is_empty(l)){
        new_list = empty_list();
    } else {
        new_list = malloc(sizeof(list));
        new_list -> elem = l -> elem;
        new_list -> next = copy (l -> next);
    }
    return new_list;
}

void destroy_list(list l){
    if (!is_empty(l)) {
        destroy_list(l->next);
        free(l);
    }
}
