#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int i;
    unsigned int j;
    unsigned int ppiv;
    ppiv = izq;
    i = izq+1;
    j = der;
    while (i<=j){
        if (goes_before(a[i], a[ppiv])){
            i++;
        }
        else if (goes_before(a[ppiv], a[j])){
            j--;
        }
        else if (goes_before(a[ppiv], a[i]) && goes_before(a[j], a[ppiv])){
            swap(a, i, j);
        }
        }

    swap(a, ppiv, j);
    ppiv = j;

    /* Permutes elements of a[izq..der] and returns pivot such that:
     - izq <= pivot <= der
     - elements in a[izq,pivot) all 'go_before' (according to function goes_before) a[pivot]
     - a[pivot] 'goes_before' all the elements in a(pivot,der]
    */
    return ppiv;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;
    if (der > izq){
        ppiv = partition(a, izq, der);
        quick_sort_rec(a, izq, (ppiv == 0) ? 0u : ppiv - 1);
        quick_sort_rec(a, ppiv+1u, der);
    }
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}


