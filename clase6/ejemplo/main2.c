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
    int id_memoria;
    dato *memoria = NULL;
    int i;
    int id_semaforo;

    memoria = (dato *)creo_memoria(sizeof(dato) * CANTIDAD, &id_memoria, CLAVE_BASE);
    id_semaforo = creo_semaforo();
    /*Memset*/

    while (1)
    {
        espera_semaforo(id_semaforo);
        /*Menu/Logica consumidor*/
        printf("Leemos la memoria\n");
        for (i = 0; i < CANTIDAD; i++)
        {
            printf("Leido %d %c\n", memoria[i].numero, memoria[i].letra);
        }
        printf("Dejamos de leer la memoria\n");
        levanta_semaforo(id_semaforo);
        usleep(10000 * MS);
    }
    /* Libero la memoria compartida */
    shmdt((char *)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
