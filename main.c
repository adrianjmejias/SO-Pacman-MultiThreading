/*
estructura del programa
1- comentarios
2- includes < >
3- includes " "
4- variables globales y globales extern
5- constantes y macros
6- typedefs
7- prototipos de funciones
8- declaracion variables globales
9- implementacion de funciones
*/

#include "Despachador.h"
void Agregar_Procesos(Cola_Procesos *, Despachador *, int);
/*Ordena la entrada por orden de llegada*/
void Ordenar_Entrada(Cola_Procesos *cola);
/*Indica si pro_a tienen un tiempo de llegada menor que pro_b*/
bool Llego_Antes(Proceso *pro_a, Proceso *pro_b);

int main(int argc, char *argv[])
{
	int ii;
	int tiempo = 0;
	Cola_Procesos *cola_buffer = New_Cola_Proceso();
	Cola_Procesos *cola_entrada = Leer_Lista_Procesos(argv[1]);
	Despachador *despachador;
	despachador = New_Despachador(2, 1, 1, 2);
	despachador->cola[PRI_1].quantum = 3;
	despachador->cola[PRI_2].quantum = 2;
	despachador->cola[PRI_3].quantum = 1;

	Ordenar_Entrada(cola_entrada);

	do // while(!Esta_Vacio(despachador) || !Cola_Empty(cola_entrada)
	{
		printf("tiempo %d*********************************\n", tiempo);

		//Asegura que los recursos son dados a los procesos de mayor prioridad
		Cola_Ordenar(&despachador->cola[BLOQUEO]);
		Agregar_Procesos(&despachador->cola[BLOQUEO], despachador, MAX_INT);

		//Pasa los Procesos que se van a ejecutar en el segundo actual
		Cola_Transferir(cola_entrada, cola_buffer, tiempo);
		//Asegura que los recursos son dados a los procesos de mayor prioridad
		Cola_Ordenar(cola_buffer);
		Agregar_Procesos(cola_buffer, despachador, tiempo);

		CPU_Planificar(despachador, tiempo);
		tiempo++;
	} while (!Despachador_Empty(despachador) || !Cola_Empty(cola_entrada));
	

	return 0;
}

//****************************************************************************
/*
Esta funcion se encarga de agregar los procesos que ya hayan llegado
y tengan disponibles los recursos necesarios para su ejecucion
*/
void Agregar_Procesos(Cola_Procesos *entrada, Despachador *des, int tiempo)
{
	int ii = 0;
	Proceso *pro = Cola_Front(entrada);
	int size = entrada->size;
	for (ii = 0; ii < size && pro->t_llegada <= tiempo; ii++)
	{
		if (Recursos_Verificar(des, pro))
		{
			p("Agrego proceso a despachador");
			Recursos_Asignar(des, pro);
			//Print_Arreglo(des->recurso, NUM_RECURSOS);

			Despachador_Push(des, pro);
		}
		else
		{
			p("Agrego proceso a bloqueo");
			//Print_Arreglo(des->recurso, NUM_RECURSOS);
			Cola_Push(&des->cola[BLOQUEO], pro);
		}
		pro = Cola_Pop(entrada);
		pro = Cola_Front(entrada);
	}//Fin forque recorre cola entrada
}//Fin funcion Agregar_Procesos

bool Llego_Antes(Proceso *pro_a, Proceso *pro_b)
{
	return pro_a->t_llegada < pro_b->t_llegada;
}

void Ordenar_Entrada(Cola_Procesos *cola)
{
	Nodo *nodo_actual;
	int ii, jj, tam_cola = cola->size;

	for (ii = 1; ii < tam_cola; ++ii)
	{
		nodo_actual = cola->first;
		for (jj = 0; jj < tam_cola - ii; ++jj)
		{
			if (Llego_Antes(nodo_actual->next->data, nodo_actual->data))
			{
				Nodo_Swap(nodo_actual, nodo_actual->next);
			}
			nodo_actual = nodo_actual->next;
		}

		//Print_Proceso(nodo_actual->data);
		//nodo_actual = nodo_actual->next;
	}
	//return cola;
}
