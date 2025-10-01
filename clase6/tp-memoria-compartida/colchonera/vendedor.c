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
    descripcion *memoria = NULL;
    int id_semaforo;
    int codigo;
    int cantidad;
    memoria = (descripcion *)creo_memoria(sizeof(descripcion) * CANTIDAD, &id_memoria, CLAVE_BASE);
    if (!inExisteArchivo("semaforoInicializado.dat")) {
        printf("No se inicializo el semaforo. Debe correr el programa colchoneria primero\n");  
        voCerrarArchivo();
        exit(0);
    }
    id_semaforo = creo_semaforo();
    printf("Menu vendedor\n");

    while (1)
    {
        espera_semaforo(id_semaforo);
        while(1) {
            printf("Ingrese un codigo (1-5), 0 para salir: ");
            scanf("%d", &codigo);
            if(codigo == 0){
                printf("Saliendo del programa\n");
                levanta_semaforo(id_semaforo);
                return 0;
            }
            if(codigo < 1 || codigo > 5){
                printf("Codigo invalido, debe ser entre 1 y 5\n");
                continue;
            }
            break; /*Si el codigo es valido, salimos del while*/
        }
        printf("Ingrese una cantidad (Stock: actual %d): ", memoria[codigo].cantidad);
        scanf("%d", &cantidad);
        if(memoria[codigo].cantidad < cantidad){
            printf("No hay suficiente stock, debe ser menor o igual a %d\n", memoria[codigo].cantidad);
            printf("Ingrese una cantidad (Stock actual:  %d): ", memoria[codigo].cantidad);
            scanf("%d", &cantidad);
        }
        memoria[codigo].cantidad -= cantidad;
        printf("Se vendieron %d colchones %s\n", cantidad, memoria[codigo].nombre);
        printf("Stock actual %s: %d\n", memoria[codigo].nombre, memoria[codigo].cantidad);
        levanta_semaforo(id_semaforo);
        usleep(500 * MS);
    }
    /* Libero la memoria compartida */
    shmdt((char *)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
