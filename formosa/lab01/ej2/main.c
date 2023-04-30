/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_stdin(int array[],
                             unsigned int max_size){
    //your code here!!!
    unsigned int size;
    int count;

    printf("Enter the length of the array: ");
    scanf("%u", &size);
    
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
        printf("Enter the number for the %d position: ", i);
        count = fscanf(stdin, "%d", &array[i]);
        if(count!=1){
            printf("ERROR READING INPUT");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    
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


int main(void) {
    
    int array[MAX_SIZE];
    
    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
