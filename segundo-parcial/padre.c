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
/*     int *memoria;
 */    int  i;
    pthread_t idHilo[CANT_JUGADORES];
    pthread_attr_t atributos;
    DatosJugador datos[CANT_JUGADORES];

    memset(datos, 0, sizeof(datos));
    memset(idHilo, 0, sizeof(idHilo));

    /*Verifico que exista el archivo flag */
    verificar_archivo_flag();


    /* Conecto a memoria compartida para leer pasos totales */
    /* memoria = (int *)creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE); */
    printf("Preparando hilos\n");

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&mutex, NULL);

    srand(time(NULL));

    /* Le paso los datos a cada hilo */
    for (i = 0; i < CANT_JUGADORES; i++) {
        datos[i].id_cola_mensajes = id_cola_mensajes;
        datos[i].id_jugador = i;
        pthread_create(&idHilo[i], &atributos, thread_jugador, &datos[i]);
    }
    
    for (i = 0; i < CANT_JUGADORES; i++) {
        pthread_join(idHilo[i], NULL);
    }
    

    return 0;       
}
