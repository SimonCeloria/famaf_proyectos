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

unsigned int array_from_file(unsigned int indexes[], 
                             char letters[], 
                             unsigned int max_size, 
                             const char *filepath){
    FILE *fp;
    unsigned int size;
    unsigned int check_fscanf;

    fp = fopen(filepath, "r");
    if(fp==NULL){
        fprintf(stderr, "Failed to open the file\n");
        exit(EXIT_FAILURE);
    }

    size = 0;
    while( (!feof(fp)) && (size<max_size)){
        check_fscanf = fscanf(fp, " %u -> *%c* ", &indexes[size], &letters[size]);
        
        if (check_fscanf != 2){
            fprintf(stderr, "Error reading file\n");
            exit(EXIT_FAILURE);
        }
        if (indexes[size]>MAX_SIZE){
            fprintf(stderr, "Too big of an index detected!\n");
            exit(EXIT_FAILURE);
        }

        size++;
    }
    fclose(fp);

    return size;
}

void sort_phrase(unsigned int indexes[], char letters[], char sorted[], unsigned int length){
    unsigned int real_index;
    for (unsigned int i = 0; i < length; ++i){
        real_index = indexes[i];
        sorted[real_index] = letters[i];
    }
}

int main(int argc, char *argv[]) {
    
    if (argc<2){
        fprintf(stderr, "Too few arguments. Expected 2.\n");
        exit(EXIT_FAILURE);
    }

    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0;
    char *filepath = argv[1]; 
    
    length = array_from_file(indexes, letters, MAX_SIZE, filepath);

    sort_phrase(indexes, letters, sorted, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

