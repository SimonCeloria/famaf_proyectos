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

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size) {
    unsigned int r_files,i,index;
    r_files = 0u;
    i = 0u;
    FILE*archivo;    

    archivo = fopen(path,"r");
    
    while(!feof(archivo) && i < max_size) {
        fscanf(archivo,"%u -> *%c*\n",&index, &letters[i]);
        if(i >= max_size){
            printf("Existen mas elementos que el maximo permitido\n");
            exit(EXIT_FAILURE);
        }
        indexes[i] = index;
        i++;
    }
    r_files = i;
    fclose(archivo);
    return r_files;
}

int main(int argc, char *argv[]) {
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 
    //  .----------^
    //  :
    // Debe guardarse aqui la cantidad de elementos leidos del archivo
    
    if(argc != 2) {
        printf("Se espera un archivo como argumento\n");
        exit(EXIT_FAILURE);
    }

    length = data_from_file(argv[1],indexes,letters,MAX_SIZE);

    for(unsigned int i = 0u; i < length-1; i++) {
        sorted[indexes[i]] = letters[i];
    }

    dump(sorted, length);
    return EXIT_SUCCESS;
}

