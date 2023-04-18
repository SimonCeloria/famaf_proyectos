#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    if( x>=0 ){
        *y = x;
    } else {
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;
    int *p_res = NULL;
    //Inicializo un puntero p_res y lo dirijo a la posición de res.
    p_res = &res;
    a = -10;
    absolute(a,p_res);
    printf("Absolute = %d.\n",res);
    //Printea el valor de res cambiado por la función.
    return EXIT_SUCCESS;
}

