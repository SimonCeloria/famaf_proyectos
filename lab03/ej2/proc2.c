#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    if(x >= 0) {
        *y = x;
    } else {
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    a = -10;

    int *pointer_to_res = NULL;
    pointer_to_res = &res;

    absolute(a,pointer_to_res);

    printf("%d \n", res);
    //Printea correctamente el valor absoluto de a
    //C solo tiene parametros de tipo in y de tipo out, no exite un parametro in/out
    return EXIT_SUCCESS;
}

