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
    juego *memoria = NULL;
    int i, aleatorio;
    int id_semaforo;
    int pienso_un_numero;
    memoria = (juego *)creo_memoria(sizeof(juego) * CANTIDAD, &id_memoria, CLAVE_BASE);
    memset(memoria, 0, sizeof(juego) * CANTIDAD);

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);
    while (1)
    {
        espera_semaforo(id_semaforo);
        /*Menu/Logica productor*/
        srand(time(NULL));
        pienso_un_numero = inDevolverNumeroAleatorio(DESDE, HASTA);
        printf("Numero: %d\n", pienso_un_numero);
        while(1){
        memoria[i].numero_pensado = 0;
        memoria[i].estado_acierto = 0;
        if(memoria[i].numero_pensado != 0 && memoria[i].estado_acierto == 0){
            if(memoria[i].numero_pensado == pienso_un_numero){
                memoria[i].estado_acierto = 1;
            }else{
                memoria[i].numero_pensado = 0;
                memoria[i].estado_acierto = 0;
            }
        }
        if(memoria[i].estado_acierto == 1){
            printf("Jugador ganador: %s\n", memoria[i].nombre_jugador);
            memoria[i].numero_pensado = 0;
            memoria[i].estado_acierto = 0;
            break;
        }
    }
        levanta_semaforo(id_semaforo);
        usleep(10000 * MS);
    }
    /* Libero la memoria compartida */
    shmdt((char *)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
