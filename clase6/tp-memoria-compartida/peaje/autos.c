#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "memoria.h"
#include "archivos.h"
#include "semaforos.h"
#include "clave.h"
#include "def.h"
#include "funciones.h"

int main(int argc, char *argv[])
{
    /*Declaracion de variables*/
    int id_memoria;
    int *vehiculos_en_cola;
    int id_semaforo;
    int cantidad_de_vias;
    int via_seleccionada;
    int i;
    int minimo;
    char buffer[LARGO];
    
    /*Semilla para numeros aleatorios*/
    srand(time(NULL) + 1);
    
    /*Me conecto a la memoria compartida creada por PEAJE*/
    vehiculos_en_cola = (int *)creo_memoria(sizeof(int) * MAX_VIAS, &id_memoria, CLAVE_BASE);
    
    /*Leo la cantidad de vias del archivo (si falla, PEAJE no fue ejecutado, y no se inicializo el semaforo)*/
    if(!inAbrirArchivo("vias.dat", "r") || !inLeerArchivo(buffer)){
        printf("Error: Debe correr el programa PEAJE primero\n");
        exit(0);
    }
    cantidad_de_vias = atoi(buffer);
    voCerrarArchivo();
    
    id_semaforo = creo_semaforo();
    printf("AUTOS\n");

    while (1)
    {
        espera_semaforo(id_semaforo);
        /*Verifico si PEAJE finalizo. Si queremos que corra infinitamente, se puede sacar esta condicion*/
        if(!inExisteArchivo("vias.dat")){
            printf("\nPeaje llego a %d liberaciones. Finalizo.\n", MAX_LIBERACIONES);
            break;
        }
        
        /*Busco la via con menos autos en la memoria compartida*/
        obtener_via_con_menos_vehiculos(vehiculos_en_cola, cantidad_de_vias, &via_seleccionada, &minimo, &i);
        /*Agrego un auto a la via seleccionada en la memoria compartida*/
        vehiculos_en_cola[via_seleccionada]++;
        printf("Se agrego 1 auto a la VIA [%d]. Total: %d autos.\n", 
               via_seleccionada + 1, vehiculos_en_cola[via_seleccionada]);
        
        levanta_semaforo(id_semaforo);
        usleep(inDevolverNumeroAleatorio(400, 600) * MS);
    }
    
    /* Libero la memoria compartida */
    shmdt((int *)vehiculos_en_cola);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);

    return 0;
}
