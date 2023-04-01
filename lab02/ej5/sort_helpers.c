#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "fixstring.h"

void swap(fixstring a[], unsigned int i, unsigned int j) {

    fixstring tmp;
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;

}

bool goes_before(fixstring x, fixstring y) {

    // Defino variable local y por defecto asigno false a its_less porque el if solo va a devolver true si es menor
    bool its_less = false;

    if (x[0] <= y[0]) //Solo en el caso de que la primer vocal de la palabra si es alfabeticamente menor que la primer vocal de la segunda palabra va a retornar true
    {
        its_less = true;
    }

    return its_less;
}

bool array_is_sorted(fixstring array[], unsigned int length) {
    unsigned int i = 1;
    while (i < length && goes_before(array[i-1], array[i])) {
        i++;
    }
    return (i >= length);
}

