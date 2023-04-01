#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"


unsigned int fstring_length(fixstring s) {
    //Defino variables locales

    unsigned int word_length; 
    unsigned int i;
    //Defino el largo minimo posible del arreglo y el tamaño minimo de la palabra

    i = 0;
    word_length = 0;

    //Bucle para determinar el largo

    while((s[i] != '\0')) //Mientras el elemento del arreglo sea distinto de '/0' (nos dice que el arreglo de char llego al final) va a iterar
    {
        word_length = word_length + 1; // En cada iteracion sumo uno al contador del largo d ela palabra
        i = i + 1; //Sumo 1 a i para ir avanzando en el array hasta llegar al final donde se encuentra '/0'
    }

    return word_length; //Retorno el largo de la palabra
}

bool fstring_eq(fixstring s1, fixstring s2) {
    //Defino variables locales, le asigno true porque si el bucle no encuentra un elemento distinto significa que son iguales

    unsigned int i = 0;
    bool its_eq = true;

    //Bucle para encontrar un elemento distinto entre ambas palabras

    while((s1[i] != '\0') || (s2[i] != '\0') ) //El bucle va a iterar siempre y cuando ambas palabras llegen al final de su arreglo
    {
        if (s1[i] != s2[i]) //Si encuentra un elemento distinto la variable its_eq retorna falso
        {
            its_eq = false;
        }
        i = i + 1; //Avanzo en el array
    }

    return its_eq; //Retorno true si son iguales, false si no son iguales
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    // Defino variable local y por defecto asigno false a its_less porque el if solo va a devolver true si es menor

    bool its_less = false;

    if (s1[0] <= s2[0]) //Solo en el caso de que la primer vocal de la palabra si es alfabeticamente menor que la primer vocal de la segunda palabra va a retornar true
    {
        its_less = true;
    }

    return its_less; //Retorno true si es menor o igual en sentido alfabetico
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;
    aux = fstring_set(aux,s1);
    s1 = fstring_set(s1,s2);
    s2 = fstring_set(s1,aux);
}


