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

int main(int argc, char *argv[])
{
    int vector_tambor[MAX_CANT_JUGADORES];
    int cantidad_jugadores;
    int i;
    pthread_t *idHilo;
    pthread_attr_t atributos;
    int *numero_jugador_eliminado;
    DatosJugador *datos;
    

    cantidad_jugadores = MAX_CANT_JUGADORES;
    
    /* Inicializo el vector tambor en 0 */
    for (i = 0; i < MAX_CANT_JUGADORES; i++) {
        vector_tambor[i] = 0;
    }
    
    /* creo el array de hilos de jugadores con memoria dinamica*/
    idHilo = (pthread_t *) malloc(sizeof(pthread_t) * cantidad_jugadores);
    datos = (DatosJugador *) malloc(sizeof(DatosJugador) * cantidad_jugadores);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    printf("Ruleta rusa\n");
    
    /* Inicializo los datos de los hilos de jugadores y creo los hilos */
    for (i = 0; i < cantidad_jugadores; i++) {
        datos[i].vector_tambor = vector_tambor;
        datos[i].numero_jugador = i;
        pthread_create(&idHilo[i], &atributos, thread_jugador, &datos[i]);
    }

    /* Espero a que terminen los hilos de jugadores y muestro el numero del jugador eliminado */
    for (i = 0; i < cantidad_jugadores; i++) {
        pthread_join(idHilo[i], (void **) &numero_jugador_eliminado);
        if (numero_jugador_eliminado != NULL) {
            if (i == 0) {
                printf("Resultado final: El jugador %d fue eliminado\n", *numero_jugador_eliminado);
            }
            free(numero_jugador_eliminado);
        }
    }   
    
    /*Libero la memoria dinamica*/
    free(idHilo);
    free(datos);

    return 0;       
}
