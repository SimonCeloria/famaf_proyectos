#include "mybool.h"
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath) {
    //your code here!!!
    FILE *fp;
    unsigned int size;
    int count;

    fp = fopen(filepath, "r");
    if(fp==NULL){
        printf("Failed to open the file\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%u", &size);
    
    if(size>max_size){
        printf("EXCEEDED MAX SIZE"); //Tambien pasa si el tamaño es negativo, es porque la variable es unsigned
        exit(EXIT_FAILURE);
    }

    /*
    if(size==0){
        printf("[]\n");
        exit(EXIT_SUCCESS);     Lo del exit no era la mejor forma... Ahora me doy cuenta porque no puedo imprimir si el arreglo
                                esta ordenado cuando es vacio. Quiza sea un poco obvio si es vacio, pero me gustaria añadir una aclaracion.
    }
    */

    unsigned int i=0;
    while(i<size){  //De todas formas esto funciona sin la funcion de arriba, no se ni por que la hice.
        count = fscanf(fp, "%d", &array[i]);
        if(count!=1){
            printf("ERROR READING FILE");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    fclose(fp);
    
    return size;
}

void array_dump(int a[], unsigned int length) {
    //your code here!!!
    if(length==0){
        printf("[]\n");
    }
    else{
        unsigned int i=0;
        printf("[");
        while(i+1<length){
            printf("%d, ", a[i]);
            i++;
        }
        printf("%d", a[i]);
        printf("]\n");
    }
}

mybool array_is_sorted(int a[], unsigned int length) {
    unsigned int i=0;
    mybool issorted = true;
    while(i<length){
        if(a[i-1]>a[i]){
            issorted = false;
        }
        i++;
    }

    return issorted;
}

void array_swap(int a[], unsigned int i, unsigned int j){
    int temp;
    temp = a[i];
    
    a[i] = a[j];
    a[j] = temp;
}