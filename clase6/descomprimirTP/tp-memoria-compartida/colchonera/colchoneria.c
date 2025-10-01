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
    descripcion *memoria = NULL;
    int i;
    int id_semaforo;
    char nombres[5][LARGO] = {"PIERO", "SUAVESTAR", "CANNON", "SIMMONS", "BELMO"};
    
    memoria = (descripcion *)creo_memoria(sizeof(descripcion) * CANTIDAD, &id_memoria, CLAVE_BASE);
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);
    /* Creo el archivo para marcar que el semaforo esta inicializado */
    inEscribirArchivo("semaforoInicializado.dat", "1\n");    
    printf("Colchoneria\n");

    while (1)
    {
        espera_semaforo(id_semaforo);
        /*Inicializo los datos de la memoria compartida solo una vez*/
        if (!inExisteArchivo("datosInicializados.dat")) {
            /*El archivo no existe, inicializo los datos*/
            for(i = 0; i < 5; i++){
                memoria[i].cantidad = 10;
                memoria[i].codigo = i + 1;
                strcpy(memoria[i].nombre, nombres[i]);
                printf("Codigo %d. %s Stock: %d\n", memoria[i].codigo, memoria[i].nombre, memoria[i].cantidad);
            }
            /*Creo el archivo para marcar que ya se inicializaron los datos*/
            inEscribirArchivo("datosInicializados.dat", "1\n");
        }

        /*Verifico si hay colchones con menos de 10 unidades y los repongo*/
        for(i = 0; i < 5; i++){
            if(memoria[i].cantidad < 10){
                printf("El stock de %s es de %d, se repone 1 colchon.\n", (char *)memoria[i].nombre, memoria[i].cantidad);
                memoria[i].cantidad += 1;
                printf("Stock actual %s: %d\n", (char *)memoria[i].nombre, memoria[i].cantidad);
            }
        }

        levanta_semaforo(id_semaforo);
        usleep(500 * MS);
    }
    /* Libero la memoria compartida */
    shmdt((char *)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
