#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    *y = (x>=0) ? x : (-x);
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    
    int *p = NULL;
    p = &res;
    a = -10;
    absolute(a, p);
    printf("%d\n", res);

    return EXIT_SUCCESS;
}

/* 
C solo tiene ins, porque no puede modificar variables desde una funcion (outs) ya que C trabaja con copias de todas las variables durante
la ejecucion de la funcion. 
*/