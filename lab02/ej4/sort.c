#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

static unsigned int min_pos_from(int a[], unsigned int i, unsigned int length) {
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; ++j) {
        if (!goes_before(a[min_pos],a[j])) {
            min_pos = j;
        }
    }
    return (min_pos);
}

void selection_sort(int a[], unsigned int length) {
    for (unsigned int i = 0u; i < length; ++i) {
        unsigned int min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}


static void insert(int a[], unsigned int i) {
    unsigned int j;
    j = i;
    while((j > 1) && (goes_before(a[j],a[j-1]))) {
        swap(a,j-1,j);
        --j;
    }
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        insert(a, i);
    }
}


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
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}
