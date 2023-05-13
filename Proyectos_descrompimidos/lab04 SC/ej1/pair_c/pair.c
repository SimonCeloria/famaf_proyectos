#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "pair.h"


struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y){
    pair_t new_par = malloc(sizeof(struct s_pair_t));
    if(new_par == NULL){
        // Si malloc devuelve NULL es porque no se pudo asignar la memoria necesaria
        exit(EXIT_FAILURE);
    }
    new_par->fst = x;
    new_par->snd = y;
    return new_par;
}


int pair_first(pair_t p){
    return p->fst;
}

int pair_second(pair_t p){
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    int tmp = p->fst;
    p->fst = p->snd;
    p->snd = tmp;
    return p;
}

void show_pair(pair_t p) {
    printf("(%d, %d)\n", p->fst, p->snd);
}

pair_t pair_destroy(pair_t p){
    if (p!=NULL){
        free(p);
        p = NULL;
    }
    return NULL;
}

