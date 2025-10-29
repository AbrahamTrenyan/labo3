#include "def.h"
#include "thread.h"
#include "funciones.h"
#include "global.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_jugador(void *parametro)
{
    Juego *datos;
    int numero_jugador;
    int numero_pensado;
    int intentos;
    int tiempo_espera;
    int *resultado;
    int cantidad_numeros;
    int hay_ganador;

    datos = (Juego *) parametro;
    numero_jugador = datos->numero_jugador;
    numero_pensado = datos->numero_pensado;
    intentos = 0;
    cantidad_numeros = HASTA - DESDE + 1;
    
    /*Genero un array con los numeros aleatorios pensados*/
    inDevolverNumeroAleatorioNoRepetitivo(datos->numeros_intentados, DESDE, HASTA);
    
    while (intentos < cantidad_numeros) {
        pthread_mutex_lock(&mutex);
        
        if (*(datos->alguien_acerto) != 0) {
            printf("Jugador %d: Hay un ganador. Gano el jugador %d. Yo termine con %d intentos.\n", numero_jugador, *(datos->alguien_acerto), intentos);
        } else {
            /*Intento con el proximo numero del array*/
            intentos++;
            printf("Jugador %d: Intento %d: %d\n", numero_jugador, intentos, datos->numeros_intentados[intentos-1]);

            if (datos->numeros_intentados[intentos - 1] == numero_pensado) {
                /*Si acerto termino con el mensaje*/
                *(datos->alguien_acerto) = numero_jugador;
                printf("Jugador %d: Acerte el numero %d en el intento %d\n", numero_jugador, numero_pensado, intentos);
            }
        }

        hay_ganador = *(datos->alguien_acerto);
        /*Guardo el dato del ganador y desbloqueo el mutex*/
        pthread_mutex_unlock(&mutex);
        usleep(500000);
        
        if (hay_ganador != 0) {
            break; /*Si hay un ganador salgo del while*/
        }

        /*Si no hay un ganador espero antes de volver a intentar*/
        tiempo_espera = inDevolverNumeroAleatorio(500, 5000);
        usleep(tiempo_espera * 1000);
    }
    
    /*Devuelvo la cantidad de intentos*/
    resultado = (int *) malloc(sizeof(int));
    *resultado = intentos;
    pthread_exit((void *) resultado);
}
