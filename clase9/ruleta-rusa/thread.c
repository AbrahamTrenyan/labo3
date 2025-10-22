#include "def.h"
#include "thread.h"
#include "funciones.h"
#include "global.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mensajes.h"

void *thread_jugador(void *parametro)
{
    DatosJugador *datos;
    int *vector_tambor;
    int numero_jugador;
    int id_cola_mensajes;
    int numero_elegido;
    int i;
    int *resultado;
    Mensaje mensaje;
    
    datos = (DatosJugador *) parametro;
    vector_tambor = datos->vector_tambor;
    numero_jugador = datos->numero_jugador;
    
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    
    resultado = (int *) malloc(sizeof(int));
    *resultado = numero_jugador;
    
    while (1) {
        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR + numero_jugador, &mensaje);
        
        if (mensaje.int_evento == EVT_INICIO) {
            pthread_mutex_lock(&mutex);
            printf("Soy el jugador %d y voy a dispararme\n", numero_jugador);
            /*Elige el primer numero disponible del vector_tambor*/
            for (i = 0; i < MAX_CANT_JUGADORES; i++) {
                if (vector_tambor[i] == 0) {
                    vector_tambor[i] = 1;
                    numero_elegido = i + 1; 
                    break;
                }
            }
            
            printf("Soy el jugador %d y la posicion del tambor es %d\n", numero_jugador, numero_elegido);
            sprintf(mensaje.char_mensaje, "%d", numero_elegido);
            enviar_mensaje(id_cola_mensajes, MSG_REVOLVER, numero_jugador, EVT_DISPARO, mensaje.char_mensaje);
            pthread_mutex_unlock(&mutex);
        }
        else if (mensaje.int_evento == EVT_SALVADO) {
            printf("El jugador %d se salvo\n", numero_jugador);
        }
        else if (mensaje.int_evento == EVT_FIN) {
            int jugador_eliminado = atoi(mensaje.char_mensaje);
            printf("El jugador %d recibio fin del juego - Jugador %d eliminado\n", numero_jugador, jugador_eliminado);
            *resultado = jugador_eliminado;
            pthread_exit((void *) resultado);
        }
    }
    
    pthread_exit((void *) resultado);
}
