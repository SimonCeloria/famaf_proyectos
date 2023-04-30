#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    y = (x>=0) ? x : (-x);
}

int main(void) {
    int a=-10, res=9;
    absolute(a, res);
    printf("%d\n", res);

    return EXIT_SUCCESS;
}

