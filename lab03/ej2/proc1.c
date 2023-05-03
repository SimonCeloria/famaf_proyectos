#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    
    if(x >= 0) {
        y = x;
    } else {
        y = -x;
    }

}

int main(void) {
    int a=0, res=0;
    
    a = -10;
    absolute(a,res);
    printf("%d \n", res);
    //Printea el valor de res al inicializar la variable sin cambios, en este caso 0
    return EXIT_SUCCESS;
}

