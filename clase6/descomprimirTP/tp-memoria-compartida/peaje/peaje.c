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
    int i;
    int id_semaforo;
    int cantidad_de_vias;
    char buffer[LARGO];
    int cantidad_de_liberaciones;
    
    cantidad_de_liberaciones = 0;
    
    srand(time(NULL));

    /*Creo la memoria compartida para el vector de vehiculos en cola*/
    vehiculos_en_cola = (int *)creo_memoria(sizeof(int) * MAX_VIAS, &id_memoria, CLAVE_BASE);
    
    /*Inicializo el vector en 0*/
    for(i = 0; i < MAX_VIAS; i++){
        vehiculos_en_cola[i] = 0;
    }
    memset(buffer, 0, sizeof(buffer));


    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);
    
    printf("Peaje\n");
    /*Obtengo la cantidad de vias del parametro y lo escribo en el archivo para que AUTOS lo lea*/
    obtener_cantidad_de_vias(argc, argv, &cantidad_de_vias);
    sprintf(buffer, "%d\n", cantidad_de_vias);
    inEscribirArchivo("vias.dat", buffer, "w");


    
    while (cantidad_de_liberaciones < MAX_LIBERACIONES)
    {
        espera_semaforo(id_semaforo);

        /*Muestro  el total de vehículos en cola en cada vía*/
        for(i = 0; i < cantidad_de_vias; i++){
            printf("VIA [%d]: %d vehiculos.\n", i + 1, vehiculos_en_cola[i]);
        }
        printf("--------------------------------\n");
        /*Verifico si hay vehiculos en la cola y los atiendo o libero la via*/
        for(i = 0; i < cantidad_de_vias; i++){
            if(vehiculos_en_cola[i] > MAX_VEHICULOS){
                printf("La via %d tiene %d autos, se libera\n", i + 1, vehiculos_en_cola[i]);
                vehiculos_en_cola[i] = 0;
                registrar_liberacion(buffer, &cantidad_de_liberaciones);
                printf("Cantidad de liberaciones: %d\n", cantidad_de_liberaciones);
            }
            else if(vehiculos_en_cola[i] > 0){
                vehiculos_en_cola[i] -= 1;
                printf("Atiendo 1 auto en la via %d. Quedan %d autos.\n", i + 1, vehiculos_en_cola[i]);
            }
        }
        
        levanta_semaforo(id_semaforo);
        usleep(inDevolverNumeroAleatorio(100, 5000) * MS);
    }
    
    printf("\nFinalizo al llegar a %d liberaciones\n", MAX_LIBERACIONES);
    inEliminarArchivo("vias.dat");
    /* Libero la memoria compartida */
    shmdt((int *)vehiculos_en_cola);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
