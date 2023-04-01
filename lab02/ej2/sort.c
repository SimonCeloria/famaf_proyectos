#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


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

