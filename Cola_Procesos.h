/*
Estructura de datos del tipo cola que se encarga de almacenar procesos
*/
#ifndef HCOLA_PROCESOS
#define HCOLA_PROCESOS
#include <stdlib.h>
#include "Defines.h"
#include "Proceso.h"

typedef Proceso *Data;

typedef struct Nodo
{
	Data data;
	struct Nodo *next;
} Nodo;

typedef struct Cola_Procesos
{
	int quantum;
	Nodo *first;
	Nodo *last;
	int size;
} Cola_Procesos;

/*
retorna una referencia a una cola de procesos inicializada
*/
Cola_Procesos *New_Cola_Proceso();

//Retorna true si la cola pasada por parametro está vacia
bool Cola_Empty(Cola_Procesos *);
//Borra la cola y los procesos dentro de ella
void Cola_Delete(Cola_Procesos *);
//Agrega un elemento al final de la cola
void Cola_Push(Cola_Procesos *, Data);

/*
Pasa los Procesos de la primera a la segunda cola, si el tiempo del Proceso
es menor al tiempo pasado por parámetro
*/
void Cola_Transferir(Cola_Procesos *, Cola_Procesos *, int);

/*
Ordena la cola_procesos que le pasemos por parametro
basandose en la prioridad de los procesos
*/
void Cola_Ordenar(Cola_Procesos *);
/*
Retorna y desencola el primer elemento de
la cola pasada por parametro
*/
Data Cola_Pop(Cola_Procesos *);

/*
Retorna el primer elemento de la cola pasada por parametro
*/
Data Cola_Front(Cola_Procesos *);
/*
Retorna el último elemento de la cola pasada por parametro
*/
Data Cola_Back(Cola_Procesos *);

/*
retorna true si el primer proceso pasado por parámetro
tiene una prioridad mayor al segundo
*/
bool Procesos_Mayor(Proceso *, Proceso *);

/*
Intercambia los contenidos de 2 nodos
*/
void Nodo_Swap(Nodo *, Nodo *);
/*
se le pasa el nombre de un archivo del tipo listaprocesos
y genera una Cola_Procesos con los procesos dentro de el
*/
Cola_Procesos *Leer_Lista_Procesos(const char *);

#endif //HCOLA_PROCESOS
