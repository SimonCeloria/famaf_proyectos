#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

typedef struct{
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
}bound_data;

bound_data check_bound(int value, int arr[], unsigned int length) {
    bound_data res;
    res.is_upperbound=true;
    res.is_lowerbound=true;
    res.exists=false;
    unsigned int lowpos=0;
    unsigned int uppos=0;
    unsigned int i = 0;
    while(i<length){
        if (value>arr[i]){
            res.is_lowerbound = false;}
        if (value<arr[i]){
            res.is_upperbound = false;}
        if (arr[i]<=arr[lowpos]){
            lowpos = i;}
        if (arr[i]>=arr[uppos]){
            uppos = i;}
        if (value==arr[i]){
            res.exists=true;}
        i++;
        }
    if (res.is_lowerbound){
        res.where=lowpos;}
    if (res.is_upperbound){
        res.where=uppos;}
    return res;
}

void pedirArreglo(int a[], int length){
    int i=0;
    printf("Íngrésé los elementos del arreglo:\n");
    while (i<length){
        printf("Elemento de la posicion %d: \n", i);
        scanf("%d", &a[i]);
        i++;
        }
    }
    
int main(void) {
    int a[ARRAY_SIZE];
    pedirArreglo(a, ARRAY_SIZE);
    printf("Ingrese el valor a comparar: ");
    int value;
    scanf("%d", &value);
    bound_data result = check_bound(value, a, ARRAY_SIZE);
    if (result.exists==false){
        printf("El elemento esta fuera del arreglo, por lo tanto no es minimo ni maximo\n");
        }
    if (result.is_upperbound){
        printf("El valor es cota superior ");
        if (result.exists){
            printf("El valor es maximo porque esta dentro del arreglo\n");
        }
        }     
    if (result.is_lowerbound){
        printf("El valor es cota inferior ");
        if (result.exists){
            printf("El valor es minimo porque esta dentro del arreglo\n"); 
        }
        }   
    if (result.exists && (result.is_upperbound || result.is_lowerbound)){
        printf("El elemento esta en la posicion %u\n", result.where);  
        }  
        
    return EXIT_SUCCESS;
}

