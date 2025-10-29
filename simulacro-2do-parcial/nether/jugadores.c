#include "def.h"    
#include "funciones.h"
#include "global.h"
#include "thread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "archivos.h"
#include "memoria.h"
#include "mensajes.h"

int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    int id_memoria;
    int *memoria;
    int i;
    pthread_t idHilo[4];
    pthread_attr_t atributos;
    DatosJugador datos[4];
    
    /*Verifico que exista el archivo flag */
    if (!inExisteArchivo(ARCHIVO_FLAG)) {
        printf("El juego no inicio, debe correr el proceso tablero\n");
        return 1;
    }
    /* Conecto a memoria compartida para leer pasos totales */
    memoria = (int *)creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    printf("Pasos para llegar a la meta: %d\n", *memoria);
    printf("Preparando jugadores\n");
    



    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    /* Configuro atributos de hilos */
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    /* Le paso el id de la cola de mensajes y el tipo de personaje a cada hilo */
    for (i = 0; i < 4; i++) {
        datos[i].id_cola_mensajes = id_cola_mensajes;
        datos[i].tipo_personaje = i; /* 0=Steve, 1=Piglin, 2=Zombie, 3=Creeper */
    }
    i = 0;
    /* Creo los 4 hilos */
    for (i = 0; i < 4; i++) {
        pthread_create(&idHilo[i], &atributos, thread_jugador, &datos[i]);
    }
    i = 0;

    /* Espero a que terminen los hilos */
    for (i = 0; i < 4; i++) {
        pthread_join(idHilo[i], NULL);
    }


    return 0;       
}
