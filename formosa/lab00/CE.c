#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void pedirArreglo(int a[], int length){
    int i=0;
    printf("Ingrese los elementos del arreglo:\n");
    while (i<length){
        printf("Elemento de la posicion %d: \n", i);
        scanf("%d", &a[i]);
        i++;
        }
    }

int main(void){

    return 0;
    }
