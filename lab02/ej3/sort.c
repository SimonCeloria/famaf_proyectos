#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
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
    /* Permutes elements of a[izq..der] and returns pivot such that:
     - izq <= pivot <= der
     - elements in a[izq,pivot) all 'go_before' (according to function goes_before) a[pivot]
     - a[pivot] 'goes_before' all the elements in a(pivot,der]
    */
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;

    if (der > izq)
    {
      ppiv = partition(a,izq,der); // Obtengo el pivote usando partition
      quick_sort_rec(a,izq,ppiv-1);  // Ordeno desde el principio del array hasta antes del pivot
      quick_sort_rec(a,ppiv+1,der); // Ordeno desde el principio del array hasta despues del pivot
    }

}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

