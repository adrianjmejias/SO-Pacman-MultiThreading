#ifndef HPROCESO
#define HPROCESO
#include <unistd.h> //pid_t
#include "Defines.h"
//https://stackoverflow.com/questions/1675351/typedef-struct-vs-struct-definitions

/*
a los procesos se le dan los recursos cuando pasa de la cola[USUARIO] a cualquiera de las otras colas
y ellos devuelven los recursos solo cuando mueren


Los procesos son simulados por el despachador creando un nuevo proceso por cada proceso despachado.
 Cada proceso debe mostrar lo siguiente:
1. Un mensaje que muestre el ID del proceso cuando este empiece.
2. Un mensaje cada segundo que el proceso se esté ejecutando.
3. Un mensaje cuando el proceso se suspenda, continúe o termine.
*/

typedef struct Proceso
{
	pid_t pid;
	int t_ejecucion;
	int t_llegada;
	int t_restante;
	int prioridad;
	int recurso_necesario[NUM_RECURSOS];
	bool es_nuevo;
} Proceso;

//Inicializa un proceso
Proceso *New_Proceso(int, int, int, int, int, int, int);
void Proceso_Print(Proceso *);

#endif //HPROCESO
