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
    int cantidad_jugadores;
    int numero_pensado;
    int alguien_acerto;
    int i;
    pthread_t *idHilo;
    pthread_attr_t atributos;
    Juego *datos_thread;
    int *intentos_thread;
    
    alguien_acerto = 0;

    cantidad_jugadores = obtenerCantidadJugadores(argc, argv);
    /* Con memoria dinamica creo el array de hilos de jugadores*/
    idHilo = (pthread_t *) malloc(sizeof(pthread_t) * cantidad_jugadores);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    /* Con memoria dinamica creo el array de datos de los hilos de jugadores*/
    datos_thread = (Juego *) malloc(sizeof(Juego) * cantidad_jugadores);


    printf("Pienso un numero desde %d hasta %d\n", DESDE, HASTA);
    srand(time(NULL));
    numero_pensado = inDevolverNumeroAleatorio(DESDE, HASTA);
    printf("El numero pensado es: %d\n", numero_pensado);
    printf("Cantidad de jugadores: %d\n\n", cantidad_jugadores);

    /* Inicializo los datos de los hilos de jugadores y creo los hilos */
    for (i = 0; i < cantidad_jugadores; i++) {
        datos_thread[i].numero_pensado = numero_pensado;
        datos_thread[i].alguien_acerto = &alguien_acerto;
        datos_thread[i].numero_jugador = i + 1;
        pthread_create(&idHilo[i], &atributos, thread_jugador, &datos_thread[i]);
    }

    /* Espero a que terminen los hilos de jugadores y muestro los intentos de cada jugador */
    for (i = 0; i < cantidad_jugadores; i++) {
        pthread_join(idHilo[i], (void **) &intentos_thread); /*Recibo el puntero a la variable intentos_thread con la cantidad de intentos*/
        printf("Padre: Ya termino el thread jugador %d con %d intentos\n", i + 1, *intentos_thread);
        free(intentos_thread);
    }
    
    if (alguien_acerto > 0) {
        printf("\nGano el jugador %d\n", alguien_acerto);
    }

    /*Libero las variables de memoria dinamica*/
    free(idHilo);
    free(datos_thread);

    return 0;   
}
