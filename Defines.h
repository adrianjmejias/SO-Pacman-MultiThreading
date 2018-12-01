#ifndef HDEFINES
#define HDEFINES
#include "Funciones.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#define p(msg) printf("%s\n", msg)
#define MAYOR(procesoa, procesob) procesoa < procesob
#define MENOR(procesoa, procesob) procesoa > procesob
#define IGUAL(procesoa, procesob) procesoa == procesob
#define MOSTRAR_ESTADO_PROCESO(proc, estado_proceso) printf("El proceso %d esta %s\n", proc, estado_proceso)
#define REDUCIR_PRI(a) a = (a < MIN_PRI) ? a + 1 : a;
//En cuanto a cantidades
#define NUM_RECURSOS 4
#define NUM_COLAS 5

// En cuanto a recursos
#define IMPRESORA 0
#define SCANNER 1
#define MODEM 2
#define DVD 3

//En cuanto a colas
#define NINGUNO 1 << 30 //pongo un numero alto para que tenga la menor prioridad

//En cuanto a las colas, qué indice se les da dentro del arreglo de colas de despachador
#define REAL 0
#define PRI_1 REAL + 1
#define PRI_2 PRI_1 + 1
#define PRI_3 PRI_2 + 1
#define BLOQUEO PRI_3 + 1
#define MIN_PRI PRI_3
#define MAX_PRI REAL
#define T_MAX 20
#define MAX_INT 1 << 30

//Implementación de booleano
typedef int bool;
#define true 1
#define false 0

#endif //HDEFINES
