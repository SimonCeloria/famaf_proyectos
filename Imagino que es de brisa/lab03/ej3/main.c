#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){
    unsigned int size = 0u, i = 0u, index;

    FILE *file_reader;
    file_reader = fopen(path,"r");
    
    while(!feof(file_reader) && i < MAX_SIZE){
        fscanf(file_reader, "%u -> *%c*\n", &index, &letters[i]);
        if(i >= max_size){
            printf("El archivo excede el maximo de elementos permitidos: %d\n", MAX_SIZE);
            exit(EXIT_FAILURE);
        }
        indexes[i] = index;
        i++;
    }
    size = i;
    fclose(file_reader);
    return size;
}

int main(int argc, char *argv[]) {
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 
    //  .----------^
    //  :
    // Debe guardarse aqui la cantidad de elementos leidos del archivo
    
    if (argc == 1){
        printf("Se espera un archivo como arguemento\n");
        exit(EXIT_FAILURE);
    }
    //Chequeamos que se nos haya mandado un archivo.
    length = data_from_file(argv[1],indexes,letters,MAX_SIZE);
    
    for(unsigned int i = 0u; i < length; i++) {
        sorted[indexes[i]] = letters[i];
    }
    /* -- completar -- */

    dump(sorted, length);

    return EXIT_SUCCESS;
}