#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
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

    if(size==0){
        printf("[]\n");
        exit(EXIT_SUCCESS); /*No se si esta sea la mejor forma, 
                            pero parecia muy conveniente ya que estamos usando tanto los exit...*/
    }

    unsigned int i=0;
    while(i<size){
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
    unsigned int i=0;
    printf("[");
    while(i+1<length){
        printf("%d, ", a[i]);
        i++;
    }
    printf("%d", a[i]);
    printf("]\n");
}