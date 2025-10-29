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
    int i;
    pthread_t idHilo[NUM_LUCHADORES];
    pthread_attr_t atributos;
    DatosLuchador datos[NUM_LUCHADORES];
    
    /* Verifico que exista el archivo flag */
    if (!inExisteArchivo(ARCHIVO_FLAG)) {
        printf("Error: ring no inicializado\n");
        return 1;
    }
    
    /* Conecto a memoria compartida */
    creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    /* Configuro atributos de hilos */
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    /* Creo datos básicos para los threads */
    for (i = 0; i < NUM_LUCHADORES; i++) {
        sprintf(datos[i].nombre, "Jugador%d", i + 1);
        datos[i].vida = 0;
        datos[i].id_luchador = i;
        datos[i].id_cola_mensajes = id_cola_mensajes;
        datos[i].equipo = (i < NUM_LUCHADORES / 2) ? 1 : 2;
    }

    /* Creo los 4 hilos luchadores */
    for (i = 0; i < NUM_LUCHADORES; i++) {
        pthread_create(&idHilo[i], &atributos, thread_luchador, &datos[i]);
    }

    /* Espero a que terminen los hilos */
    for (i = 0; i < NUM_LUCHADORES; i++) {
        pthread_join(idHilo[i], NULL);
    }

    return 0;       
}
