#include "Funciones.h"

int Suma(int a, int b)
{
    return a + b;
}

int Resta(int a, int b)
{
    return a - b;
}

void Print(int a)
{
    printf("%d ", a);
}

void Actualizar_Arreglo(int *arr1, int *arr2, int lim_inf, int lim_sup, int (*operacion)(int, int))
{
    int ii;
    for (ii = lim_inf; ii < lim_sup; ii++)
    {
        arr1[ii] = (*operacion)(arr1[ii], arr2[ii]);
    }
}

void Print_Arreglo(int *arr, int lim_sup)
{
    int ii;
    for (ii = 0; ii < lim_sup; ii++)
    {
        printf("%d ", arr[ii]);
    }
    printf("\n");
}
