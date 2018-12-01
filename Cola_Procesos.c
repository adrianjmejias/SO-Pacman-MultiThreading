#include "Cola_Procesos.h"
/*
Funciones de las colas de proceso
*/
Cola_Procesos *New_Cola_Proceso()
{
	Cola_Procesos *cola = malloc(sizeof(Cola_Procesos));
	cola->first = NULL;
	cola->last = NULL;
	cola->size = 0;
	return cola;
}

bool Cola_Empty(Cola_Procesos *cola)
{
	if (cola != NULL)
	{
		return cola->first == NULL;
	}
	else
	{
		return true;
		//perror("Error: ");
	}
}

//******************************************************************************************************

void Cola_Delete(Cola_Procesos *cola)
{
	if (cola != NULL)
	{
		while (!Cola_Empty(cola))
		{
			free(Cola_Pop(cola));
		} //Fin while delete
	}
	else
	{
		//perror("Error: ");
	}
}

//******************************************************************************************************

void Cola_Push(Cola_Procesos *cola, Data data) //Done
{
	if (data != NULL)
	{
		Nodo *nuevo_nodo = malloc(sizeof(Nodo));
		nuevo_nodo->data = data;
		nuevo_nodo->next = NULL;

		if (Cola_Empty(cola))
		{
			cola->first = nuevo_nodo;
		}
		else
		{
			cola->last->next = nuevo_nodo;
		}
		cola->last = nuevo_nodo;
		cola->size++;
	}
}

//******************************************************************************************************

//Se termine el proceso
//Cuadno se asigne a otra cola por x causa
Data Cola_Pop(Cola_Procesos *cola) //Done
{
	if (cola != NULL && !Cola_Empty(cola))
	{
		Nodo *nodo_borrar = cola->first;
		cola->first = cola->first->next;
		Data _dato = nodo_borrar->data;
		free(nodo_borrar);
		cola->size--;
		return _dato;
	}
	else
	{
		//perror("Error: ");

		return NULL;
	}
}

//******************************************************************************************************

Data Cola_Front(Cola_Procesos *cola)
{
	if (cola != NULL && !Cola_Empty(cola))
	{
		return cola->first->data;
	}
	else
	{
		//perror("Error: ");
	}
}

//******************************************************************************************************

Data Cola_Back(Cola_Procesos *cola)
{
	if (cola != NULL && !Cola_Empty(cola))
	{
		return cola->last->data;
	}
	else
	{
		//perror("Error: ");
	}
}

//******************************************************************************************************

void Cola_Transferir(Cola_Procesos *cola_a, Cola_Procesos *cola_b, int tiempo)
{
	int ii = 0, size = cola_a->size;
	Proceso *pro = Cola_Front(cola_a);
	for (ii = 0; ii < size && pro->t_llegada <= tiempo; ii++)
	{
		Cola_Push(cola_b, Cola_Pop(cola_a));
		pro = Cola_Front(cola_a);
	}
}
//******************************************************************************************************
void Cola_Ordenar(Cola_Procesos *cola)
{
	Nodo *nodo_actual;
	int ii, jj, tam_cola = cola->size;

	for (ii = 1; ii < tam_cola; ++ii)
	{
		nodo_actual = cola->first;
		for (jj = 0; jj < tam_cola - ii; ++jj)
		{
			if (Procesos_Mayor(nodo_actual->next->data, nodo_actual->data))
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

//******************************************************************************************************
bool Procesos_Mayor(Proceso *pro_a, Proceso *pro_b)
{
	return MAYOR(pro_a->prioridad, pro_b->prioridad) ||
		   (IGUAL(pro_a->prioridad, pro_b->prioridad) && pro_b->t_llegada > pro_a->t_llegada);
}

//******************************************************************************************************
void Nodo_Swap(Nodo *nodo_a, Nodo *nodo_b)
{
	Proceso *pro_temp = nodo_a->data;
	nodo_a->data = nodo_b->data;
	nodo_b->data = pro_temp;
}

//******************************************************************************************************
Cola_Procesos *Leer_Lista_Procesos(const char *nombre_archivo) //Done
{
    FILE *FILE_archivo;
    FILE_archivo = fopen(nombre_archivo, "r");
    Cola_Procesos *cola = New_Cola_Proceso();
    if (FILE_archivo == NULL)
    {
        //perror("Error en lectura de archivo.");
        return NULL;
    }

    int tiempo_llegada, prioridad, tiempo_ejec,
        n_imp, n_scan, n_modems, n_DVDs;
    while (fscanf(FILE_archivo, "%d, %d, %d, %d, %d, %d, %d\n",
                  &tiempo_llegada, &prioridad, &tiempo_ejec, &n_imp, &n_scan, &n_modems, &n_DVDs) == 7)
    {
        Proceso *proceso_actual = New_Proceso(tiempo_llegada, prioridad, tiempo_ejec,
                                              n_imp, n_scan, n_modems, n_DVDs);
        Cola_Push(cola, proceso_actual);

    } //Fin while lectura

    fclose(FILE_archivo); //Fin lectura archivo
    return cola;
}
