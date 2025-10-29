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
    DatosLuchador datos[4];

    memset(datos, 0, sizeof(datos));
    memset(idHilo, 0, sizeof(idHilo));
  
    /*Verifico que exista el archivo flag */
    while (!inExisteArchivo(ARCHIVO_FLAG)) {
        printf("El juego no inicio, debe correr el proceso tablero\n");
        sleep(2);
    }

    /* Conecto a memoria compartida para leer pasos totales */
    memoria = (int *)creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    usleep(100000);
    printf("Vida inicial: %d\n", *memoria);
    printf("Preparando luchadores\n");

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    pthread_mutex_init(&mutex, NULL);

    /* Le paso los datos a cada hilo */
    srand(time(NULL));
    for (i = 0; i < 4; i++) {
        datos[i].id_cola_mensajes = id_cola_mensajes;
        datos[i].id_jugador = i;
        if (i < 2) {
            datos[i].equipo = 1;
        } else {
            datos[i].equipo = 2;
        }
        sprintf(datos[i].nombre, "Luchador %d", i);
        pthread_create(&idHilo[i], &atributos, thread_luchador, &datos[i]);
    }
    
    printf("Todos los luchadores preparados\n");
    
    for (i = 0; i < 4; i++) {
        pthread_join(idHilo[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_attr_destroy(&atributos);

    return 0;       
}
