#ifndef HFUNCIONES
#define HFUNCIONES
#include <stdio.h>
#define MIN(a, b) (a < b) ? a : b
#define MAX(a, b) (a > b) ? a : b

//suma de enteros
int Suma(int, int);
//resta de enteros
int Resta(int, int);

/*
Esta funcion actualiza arr1, con los valores de arr2 aplicandole una operacion en especifico
dentro de lim_inf, lim_sup.
los arreglos deben ser de enteros, no nesariamente del mismo tamaño pero ambos deben existir
dentro del rango [lim_inf, lim_sup)
*/
void Actualizar_Arreglo(int *, int *, int, int, int (*operacion)(int, int));
void Print_Arreglo(int *, int);
#endif //HFUNCIONES
