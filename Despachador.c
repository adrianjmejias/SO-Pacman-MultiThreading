#include "Despachador.h"
#include <stdlib.h>
#include <stdio.h>
Despachador *New_Despachador(int impresora, int scanner, int modem, int dvd)
{
    int ii = 0;
    Despachador *des = malloc(sizeof(Despachador));
    des->recurso[IMPRESORA] = impresora;
    des->recurso[SCANNER] = scanner;
    des->recurso[MODEM] = modem;
    des->recurso[DVD] = dvd;
    des->prioridad_en_cpu = NINGUNO;
    des->proceso_en_cpu = NULL;
    for (ii = 0; ii < NUM_COLAS; ii++)
    {
        des->cola[ii].first = NULL;
        des->cola[ii].last = NULL;
        des->cola[ii].size = 0;
    }
    return des;
}
//******************************************************************************************************
void Despachador_Delete(Despachador *des) //DONE
{
  int ii;
  for (ii = 0; ii < NUM_COLAS; ii++)
  {
    Cola_Delete(&des->cola[ii]);
  }
  free(des);
}
//******************************************************************************************************
bool Despachador_Empty(Despachador *des) //DONE
{
  int ii;
  for (ii = 0; ii < NUM_COLAS; ii++)
  {
    if (!Cola_Empty(&des->cola[ii]))
    {
      return false;
    }
  }
  return des->proceso_en_cpu == NULL;
}

//******************************************************************************************************
bool Recursos_Verificar(Despachador *des, Proceso *pro) //Done
{
    if (des != NULL && pro != NULL)
    {
        int ii;
        for (ii = 0; pro->prioridad != REAL && ii < NUM_RECURSOS; ii++)
        {
            if (des->recurso[ii] < pro->recurso_necesario[ii])
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
        //perror("Error: Recursos_Verificar");
    }
}
//******************************************************************************************************
void Recursos_Asignar(Despachador *des, Proceso *pro) //Done
{
    if (des != NULL && pro != NULL)
    {
        Actualizar_Arreglo(des->recurso, pro->recurso_necesario, 0, NUM_RECURSOS, Resta);
    }
    else
    {
        //perror("Error: Recursos_Asignar");
    }
}
//******************************************************************************************************
void Recursos_Liberar(Despachador *des, Proceso *pro) //Done
{
    if (des != NULL && pro != NULL)
    {
        Actualizar_Arreglo(des->recurso, pro->recurso_necesario, 0, NUM_RECURSOS, Suma);
    }
    else
    {
        //perror("Error: Recursos_Liberar");
    }
}
//******************************************************************************************************
void CPU_Planificar(Despachador *des, int tiempo)
{
    int ii;

    //Revisa las colas desde la prioridad más alta hasta la más baja
    for (ii = MAX_PRI; ii <= MIN_PRI; ii++)
    {
        Cola_Procesos *cola_revisando = &des->cola[ii];
        Proceso *a_ejecutar;
        //Si hay procesos con mayor prioridad que yo esperando el CPU
        if (MAYOR(ii, des->prioridad_en_cpu) && !Cola_Empty(cola_revisando))
        {
            Proceso_Suspender(des);
            CPU_Asignar(des, Cola_Pop(cola_revisando));

            if (des->proceso_en_cpu->es_nuevo)
            {
                Proceso_Iniciar(des);
            }
            else
            {
                Proceso_Reanudar(des);
            }
            ii = MIN_PRI;
        }
        else if (des->prioridad_en_cpu != NINGUNO)
        {
            Proceso_Ejecutar(des);
            ii = MIN_PRI;
        }

        if (Tiempo_Verificar(des))
        {
            Proceso_Matar(des);
        }
        else if (des->quantum == 0)
        {
            Proceso_Suspender(des);
        }
    } // Fin for
} //Fin definicion CPU_Planificar
//******************************************************************************************************
void Proceso_Suspender(Despachador *des)
{
    Proceso *pro = des->proceso_en_cpu;
    if (pro != NULL)
    {
        MOSTRAR_ESTADO_PROCESO(pro->pid, "suspendido");
        kill(pro->pid, SIGSTOP);
        REDUCIR_PRI(pro->prioridad);
        Despachador_Push(des, pro);
        CPU_Liberar(des);
    }
    else
    {
        //perror("Error: Proceso_Suspender");
    }
}
//******************************************************************************************************
void Set_Quantum(Despachador *des) //Done
{
  Proceso *pro = des->proceso_en_cpu;
    if (pro->prioridad == REAL)
    {
        des->quantum = pro->t_restante;
    }
    else
    {
        des->quantum =des->cola[pro->prioridad].quantum;
    }
}
//******************************************************************************************************
bool Tiempo_Verificar(Despachador *des) //Done
{
    Proceso *pro = des->proceso_en_cpu;
    if (pro != NULL)
    {
      //verifico si se acabó el tiempo del proceso o toca matarlo porque
      //se tomó mas tiempo que T_MAX
        bool expirado = 0;
        expirado = expirado || pro->t_restante <= 0;
        expirado = expirado || (pro->prioridad != REAL && pro->t_ejecucion >= T_MAX);
        return expirado;
    }
    else
    {
        //perror("Error: Tiempo_Verificar");
        return false;
    }
}
//******************************************************************************************************
void CPU_Liberar(Despachador *des) //Done
{
    des->proceso_en_cpu = NULL;
    des->prioridad_en_cpu = NINGUNO;
    des->quantum = -1;
}
//******************************************************************************************************
void CPU_Asignar(Despachador *des, Proceso *pro) //Done
{
    des->proceso_en_cpu = pro;
    des->prioridad_en_cpu = pro->prioridad;
    Set_Quantum(des);
}
//******************************************************************************************************
void Despachador_Push(Despachador *des, Proceso *pro) //Done
{
    Cola_Push(&des->cola[pro->prioridad], pro);
}

//******************************************************************************************************
void Proceso_Iniciar(Despachador *des) //Done
{                                      //al ejecutarlo por primera vez
    Proceso *pro = des->proceso_en_cpu;
    if (des != NULL && pro != NULL)
    {
        pro->pid = fork();
        if(pro->pid != 0)
            sleep(1);

        if (pro->pid == 0)
        {
            char string_numero[6];
            sprintf(string_numero, "%d", pro->t_restante); // convertir numero a string y ponerlo en base 10
            execl( "./child", "./child", string_numero, (char *)NULL);         //si no pongo NULL recuerdo que explotaba
        }
        //printf("Mi pid: %d\n",pro->pid);
        MOSTRAR_ESTADO_PROCESO(pro->pid, "iniciando");
        Proceso_Ejecutar(des);
        pro->es_nuevo = false;
    }
    else
    {
        //perror("Error: Proceso_Iniciar");
    }
}
//******************************************************************************************************
void Proceso_Ejecutar(Despachador *des) //DONE
{
    Proceso *pro = des->proceso_en_cpu;
    if (pro != NULL)
    {
        Proceso_Print(des->proceso_en_cpu);
        //MOSTRAR_ESTADO_PROCESO(des->proceso_en_cpu->pid, "Ejecutando");
        des->quantum--;
        pro->t_restante--;
        pro->t_ejecucion++;
    }
    else
    {
        //perror("Error: Proceso_Ejecutar");
    }
}
//******************************************************************************************************
void Proceso_Matar(Despachador *des) //DONE
{
    Proceso *pro = des->proceso_en_cpu;
    if (pro != NULL)
    {
        MOSTRAR_ESTADO_PROCESO(pro->pid, "muerto");
        kill(pro->pid, SIGINT);
        Recursos_Liberar(des, pro);
        CPU_Liberar(des);
        free(pro);
    }
    else
    {
        //perror("Error: Proceso_Matar");
    }
}
//******************************************************************************************************
void Proceso_Reanudar(Despachador *des) //DONE
{
    Proceso *pro = des->proceso_en_cpu;
    if (pro != NULL)
    {
        MOSTRAR_ESTADO_PROCESO(pro->pid, "reanudandose");
        kill(pro->pid, SIGCONT);
        Proceso_Ejecutar(des);
    }
    else
    {
        //perror("Error: Proceso_Reanudar");
    }
}
//******************************************************************************************************
void Proceso_Sacar(Despachador *des) //Done
{
    if (des != NULL && des->proceso_en_cpu != NULL)
    {
        kill(des->proceso_en_cpu->pid, SIGSTOP);
        MOSTRAR_ESTADO_PROCESO(des->proceso_en_cpu->pid, "saliendo del procesador");
        Despachador_Push(des, des->proceso_en_cpu);
        CPU_Liberar(des);
    }
    else
    {
        //perror("Error: Proceso_Sacar");
    }
}
