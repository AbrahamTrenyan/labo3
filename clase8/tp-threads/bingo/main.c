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
    int bolillas[CANTIDAD_BOLILLAS];
    int cantidad_bolillas_generadas;
    int i;
    int numero_bolilla;
    int tiempo_espera;
    int *aciertos_thread;
    pthread_t *idHilo;
    pthread_attr_t atributos;
    Bingo *datos_thread;
    
    g_carton_lleno = 0;
    g_control = 0;
    cantidad_bolillas_generadas = 0;
    memset(bolillas, 0, sizeof(bolillas));

    cantidad_jugadores = obtenerCantidadJugadores(argc, argv);
    /* Con memoria dinamica creo el array de hilos de jugadores*/
    idHilo = (pthread_t *) malloc(sizeof(pthread_t) * cantidad_jugadores);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    /* Con memoria dinamica creo el array de datos de los hilos de jugadores*/
    datos_thread = (Bingo *) malloc(sizeof(Bingo) * cantidad_jugadores);
    
    srand(time(NULL));
    printf("Bingo\n");
    printf("Cantidad de jugadores: %d\n", cantidad_jugadores);
    printf("Bolillas del 1 al %d\n\n", CANTIDAD_BOLILLAS);

    /* Inicializo los datos de los hilos de jugadores y creo los hilos */
    for (i = 0; i < cantidad_jugadores; i++) {
        datos_thread[i].numero_jugador = i + 1;
        datos_thread[i].bolillas = bolillas;
        datos_thread[i].g_carton_lleno = &g_carton_lleno;
        datos_thread[i].cantidad_bolillas_generadas = &cantidad_bolillas_generadas;
        pthread_create(&idHilo[i], &atributos, thread_jugador, &datos_thread[i]);
        printf("Jugador %d creado\n", i + 1);
    }
    printf("\n");

    while (g_carton_lleno == 0 && cantidad_bolillas_generadas < CANTIDAD_BOLILLAS) {
        pthread_mutex_lock(&mutex);
        if (g_control == 0) {
            g_control = cantidad_jugadores;
            
            numero_bolilla = inGenerarNumeroAleatorioNoRepetitivo(bolillas, cantidad_bolillas_generadas, 1, CANTIDAD_BOLILLAS);
            bolillas[cantidad_bolillas_generadas] = numero_bolilla;
            cantidad_bolillas_generadas++;
            
            printf("BINGO: Salio la bolilla: %d (Total: %d)\n", numero_bolilla, cantidad_bolillas_generadas);
        }
        pthread_mutex_unlock(&mutex);
        
        tiempo_espera = inDevolverNumeroAleatorio(500, 5000);
        usleep(tiempo_espera * 1000);
    }
    
    if (g_carton_lleno != 0) {
        printf("\nHay un ganador: Jugador %d\n\n", g_carton_lleno);
    }

    /* Espero a que terminen los hilos de jugadores y muestro los aciertos de cada jugador */
    for (i = 0; i < cantidad_jugadores; i++) {
        pthread_join(idHilo[i], (void **) &aciertos_thread);
        printf("Jugador %d termino con %d aciertos\n", i + 1, *aciertos_thread);
        free(aciertos_thread);
    }

    /*Libero las variables de memoria dinamica*/
    free(idHilo);
    free(datos_thread);

    return 0;   
}
