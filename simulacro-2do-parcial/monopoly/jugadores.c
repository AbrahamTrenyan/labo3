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
    int  i;
    pthread_t idHilo[MAX_CANT_JUGADORES];
    pthread_attr_t atributos;
    DatosJugador datos[MAX_CANT_JUGADORES];
    int cantidad_jugadores;
    char buffer[LARGO_MENSAJE];
    memset(buffer, 0, sizeof(buffer));
    memset(datos, 0, sizeof(datos));
    memset(idHilo, 0, sizeof(idHilo));

    verificar_archivo_flag();

    cantidad_jugadores = obtenerCantidadJugadores(argc, argv);
    
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    
    sprintf(buffer, "%d", cantidad_jugadores);
    enviar_mensaje(id_cola_mensajes, MSG_TABLERO, MSG_JUGADOR, EVT_INICIO, buffer);
    printf("Cantidad de jugadores enviada al tablero: %d\n", cantidad_jugadores);

    /* Conecto a memoria compartida para leer plata inicial */
    memoria = (int *)
    creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE); 
    printf("Plata inicial leida de memoria compartida: $%d\n", *memoria);
    printf("Preparando hilos\n");
    
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&mutex, NULL);

    srand(time(NULL));

    /* Le paso los datos a cada hilo */
    for (i = 0; i < cantidad_jugadores; i++) {
        datos[i].id_cola_mensajes = id_cola_mensajes;
        datos[i].id_jugador = i;
        sprintf(datos[i].nombre, "Jugador %d", i + 1);
        printf("Hilo para %s creado\n", datos[i].nombre);
        pthread_create(&idHilo[i], &atributos, thread_jugador, &datos[i]);
    }
    
    for (i = 0; i < cantidad_jugadores; i++) {
        pthread_join(idHilo[i], NULL);
    }
    

    return 0;       
}
