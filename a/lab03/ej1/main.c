/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>
#include <stdlib.h>

/** @brief structure which represent a person */
typedef struct _person {
    int age;
    char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

    int x = 1;
    person_t m = {90, 'M'};
    int a[] = {0, 1, 2, 3};

    /* Completar aquí:
       Al finalizar la ejecución las variables deben tener los siguientes valores
       x = 9
       m = (100, F)
       a[1] = 42

       Las restricciones son:
       - No usar las variables 'x', 'm' y 'a' en la parte izquierda de alguna asignación.
       - Se pueden agregar líneas de código, pero no modificar las que ya existen.
       - Se pueden declarar hasta 2 punteros.
       AYUDA: podes usar GDB para consultares valores de variables y la dirección de memoria donde estan alojadas.
    */
    //Inicializamos los punteros.
    int *p_int = NULL;
    person_t *p_person = NULL;
    //Retornamos la dirección de memoria de x y cambiamos su valor.
    p_int = &x;
    *p_int = 9;
    //Retornamos la dirección de memoria de a[1] y cambiamos su valor.
    p_int = &a[1];
    *p_int = 42;
    //Retornamos la dirección de memoria de m y cambiamos su valor en cada elemento de la estructura.
    p_person = &m;
    p_person->age = 100;
    p_person->name_initial = 'F';

    printf("x = %d\n", x);
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    printf("a[1] = %d\n", a[1]
    
    //Liberamos el espacio de memoria de los punteros. 
    free(p_int);
    free(p_person);
    return EXIT_SUCCESS;
}

