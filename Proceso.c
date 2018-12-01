#include "Proceso.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> //Para los signal
//https://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code
//**************************************************************************
Proceso *New_Proceso(int t_lle, int prioridad, int t_res, int impresora,
                     int scanner, int modem, int dvd) //DONE
{
    Proceso *pro = malloc(sizeof(Proceso));
    pro->t_ejecucion = 0;
    pro->t_llegada = t_lle;
    pro->t_restante = t_res;
    pro->prioridad = prioridad;
    pro->recurso_necesario[IMPRESORA] = impresora;
    pro->recurso_necesario[SCANNER] = scanner;
    pro->recurso_necesario[MODEM] = modem;
    pro->recurso_necesario[DVD] = dvd;
    pro->es_nuevo = true;
    return pro;
}
//******************************************************************************************************
void Proceso_Print(Proceso *pro) //DONE
{
    if (pro != NULL)
    {
        printf("Ejecuto Proceso %d\n", pro->pid);
        printf("Prioridad %d\n", pro->prioridad);
        printf("Tiempo restante %d\n", pro->t_restante);
        /*printf("Recursos asignados \n");
        printf("Impresora %d\n", pro->recurso_necesario[IMPRESORA]);
        printf("Scanner %d\n", pro->recurso_necesario[SCANNER]);
        printf("Modem %d\n", pro->recurso_necesario[MODEM]);
        printf("Dvd %d\n", pro->recurso_necesario[DVD]);*/
    }
    else
    {
        //perror("Error: ");
    }
}