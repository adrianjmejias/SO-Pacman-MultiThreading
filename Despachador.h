#ifndef HDESPACHADOR
#define HDESPACHADOR
/*
El despachador contiene colas
*/
#include "Cola_Procesos.h"
#include "Proceso.h"
#include "Defines.h"

typedef struct Despachador
{
	int quantum;
	Proceso *proceso_en_cpu;
	int prioridad_en_cpu;
	Cola_Procesos cola[NUM_COLAS];
	int recurso[NUM_RECURSOS];
} Despachador;

//Retorna un despachador inicializado con los recursos que gestiona
Despachador *New_Despachador(int, int, int, int);

//Borra todas las colas de procesos (tiempo real y los de usuario)
void Despachador_Delete(Despachador *);

//Retorna true si todas las colas asociadas estan vacias
bool Despachador_Empty(Despachador *);

//Se agrega un proceso a su cola correspondiete dentro del despachador
void Despachador_Push(Despachador *, Proceso *);
/*
Toma la decisión de cuál proceso se ejecuta y le permite ejecutarse.
hace las suspenciones necesarias para ello
*/
void CPU_Planificar(Despachador *, int);

//Miscelaneous*****************************************************************
//Se le asigna el cpu a un proceso, debe hacerse antes de
//CPU_Planificar, Reanudar e Iniciar
void CPU_Asignar(Despachador *, Proceso *);

//Libera al cpu de un proceso que murio
void CPU_Liberar(Despachador *);

//Establece el quantum del proceso al CPU_Asignar
void Set_Quantum(Despachador *);

//Operaciones sobre los recursos************************************************
//Le asigna todos los recursos que necesita el proceso
void Recursos_Asignar(Despachador *, Proceso *);

//Libera los recursos que estaba usando ese proceso y hace que
//esten disponibles para los otros procesos
void Recursos_Liberar(Despachador *, Proceso *);

//Retorna true si el proceso pasado por parametro tiene los
//recurso_necesario para su ejecucion
bool Recursos_Verificar(Despachador *, Proceso *);

//Verifica si al proceso en el cpu se le acabó el tiempo de t_ejecucion excedio T_MAX
bool Tiempo_Verificar(Despachador *);


//Acciones del despachador sobre los procesos***********************************
//Inicia el proceso, y es donde se ejecuta por primera vez el exec
void Proceso_Iniciar(Despachador *);


//Suspende el proceso cuando llega otro al despachador con mayor prioridad
void Proceso_Suspender(Despachador *);


//Ejecuta el proceso en cpu
void Proceso_Ejecutar(Despachador *);


//Mata al proceso en cpu al que se le acabó el quantum o excedio T_MAX
void Proceso_Matar(Despachador *);


//Reanuda al proceso en cpu que fue suspendido o sacado del cpu
void Proceso_Reanudar(Despachador *);


//Saca al proceso que ocupa el CPU porque se le terminó el quantum
void Proceso_Sacar(Despachador *);



#endif //HDESPACHADOR
