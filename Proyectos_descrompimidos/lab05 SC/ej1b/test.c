#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


#include "stack.h"

int main() {
    stack s1;
    stack s2;
    stack s3;
    stack_elem* array;
    int test;
    test = 1;
    s1 = stack_empty();
    s2 = stack_empty();
    s3 = stack_empty();

    s1 = stack_push(s1,test);

    s2 = stack_push(s2,test);

    s3 = stack_push(s3,1);
    s3 = stack_push(s3,2);
    s3 = stack_push(s3,3);
    s3 = stack_push(s3,4);

    array = stack_to_array(s3);
    printf("%d",(int)array[0]);


    if (array != NULL) {
       // printf("%d",(int)array[0]);
        free(array);
    }
    s1 = stack_destroy(s1);
    s2 = stack_destroy(s2);
    s3 = stack_destroy(s3);
    return (EXIT_SUCCESS);
}