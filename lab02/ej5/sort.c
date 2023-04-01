#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int i,j;
    unsigned int ppiv;
    ppiv = izq;
    i = izq + 1;
    j = der;
    while(i <= j) {
        if (a[i] <= a[ppiv])
        {
            i = i + 1;
        } 
        if (a[j] >= a[ppiv]) {
            j = j - 1;
        }
        if ((a[i] < a[ppiv]) && (a[j] < a[ppiv]))
        {
            swap(a,i,j);
        }
    } 
    swap(a,ppiv,j);
    ppiv = j;

    return ppiv;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
     unsigned int ppiv;

    if (der > izq)
    {
      ppiv = partition(a,izq,der); // Obtengo el pivote usando partition
      quick_sort_rec(a,izq,ppiv-1);  // Ordeno desde el principio del array hasta antes del pivot
      quick_sort_rec(a,ppiv+1,der); // Ordeno desde el principio del array hasta despues del pivot
    }
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}


