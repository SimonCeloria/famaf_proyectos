#include <stdbool.h>
#include <stdlib.h>

#include "pair.h"


pair_t pair_new(int x, int y){
    
    pair_t new_par;
    new_par.fst = x;
    new_par.snd = y;
    return new_par;
}

int pair_first(pair_t p){
    return p.fst;
}

int pair_second(pair_t p){
    return p.snd;
}

pair_t pair_swapped(pair_t p){
    pair_t aux;
    aux.fst = p.fst;
    aux.snd = p.snd;
    p.fst = aux.snd;
    p.snd = aux.fst;
    return p;
}

pair_t pair_destroy(pair_t p){
    return p;
}

