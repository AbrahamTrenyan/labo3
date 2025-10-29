#include "def.h"
#include "thread.h"
#include "funciones.h"
#include "global.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mensajes.h"
#include "memoria.h"

void *thread_jugador(void *parametro)
{
    DatosJugador *datos;
    int id_cola_mensajes;
    int id_memoria;
    int *memoria;
    Mensaje mensaje;
    int pasos;
    int resultado;
    int done;
    int total_actual;
    
    datos = (DatosJugador *)parametro;
    id_cola_mensajes = datos->id_cola_mensajes;

    /* Me conecto a memoria compartida para obtener los pasos totales*/
    memoria = (int *)creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    
    srand(time(NULL) + datos->tipo_personaje);
    
    done = 0;
    while (!done) {
        /* Recibo mensajes del tablero */
        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR + datos->tipo_personaje, &mensaje);
        
        switch (datos->tipo_personaje) {
            case 0: /* Steve */
                if (mensaje.int_evento == EVT_AVANZA_STEVE) {
                    /* Steve se mueve SOLO cuando recibe orden específica */
                    pthread_mutex_lock(&mutex);
                    pasos = inDevolverNumeroAleatorio(2, 8);
                    total_actual = atoi(mensaje.char_mensaje) + pasos;
                    printf("Steve: Avanzo %d pasos! (total: %d/%d)\n", pasos, total_actual, *memoria);
                    sprintf(mensaje.char_mensaje, "%d", pasos);
                    enviar_mensaje(id_cola_mensajes, MSG_TABLERO, MSG_JUGADOR + datos->tipo_personaje, EVT_AVANZA_STEVE, mensaje.char_mensaje);
                    pthread_mutex_unlock(&mutex);
                    usleep(TURNO_MS * MS);

                } else if (mensaje.int_evento == EVT_INICIO) {
                    printf("Steve listo para jugar\n");
                } else if (mensaje.int_evento == EVT_MUERTE_STEVE) {
                    printf("Steve: Fui eliminado por un monstruo\n");
                    done = 1;
                } else if (mensaje.int_evento == EVT_VICTORIA_STEVE) {
                    printf("Steve: Llegue al portal, gane! \n");
                    done = 1;
                } else if (mensaje.int_evento == EVT_FIN) {
                    done = 1;
                }
                break;
                
            case 1: /* Piglin */
                if (mensaje.int_evento == EVT_AVANZA_PIGLIN) {
                    /* Piglin se mueve SOLO cuando recibe orden específica */
                    pthread_mutex_lock(&mutex);
                    pasos = inDevolverNumeroAleatorio(1, 6);
                    total_actual = atoi(mensaje.char_mensaje) + pasos;
                    printf("Piglin: Avanzo %d pasos! (total: %d/%d)\n", pasos, total_actual, *memoria);
                    sprintf(mensaje.char_mensaje, "%d", pasos);
                    enviar_mensaje(id_cola_mensajes, MSG_TABLERO, MSG_JUGADOR + datos->tipo_personaje, EVT_AVANZA_PIGLIN, mensaje.char_mensaje);
                    pthread_mutex_unlock(&mutex);
                    usleep(TURNO_MS * MS);

                } else if (mensaje.int_evento == EVT_INICIO) {
                    printf("Piglin listo para jugar\n");
                } else if (mensaje.int_evento == EVT_VICTORIA_PIGLIN) {
                    printf("Piglin: Cerre el portal!\n");
                    done = 1;
                } else if (mensaje.int_evento == EVT_FIN) {
                    done = 1;
                }
                break;
                
            case 2: /* Zombie */
                if (mensaje.int_evento == EVT_ATAQUE_ZOMBIE) {
                    pthread_mutex_lock(&mutex);
                    resultado = inDevolverNumeroAleatorio(1, 4);
                    printf("Zombie: Ataco a Steve! (resultado: %d)\n", resultado);
                    sprintf(mensaje.char_mensaje, "%d", resultado);
                    enviar_mensaje(id_cola_mensajes, MSG_TABLERO, MSG_JUGADOR + datos->tipo_personaje, EVT_ATAQUE_ZOMBIE, mensaje.char_mensaje);
                    pthread_mutex_unlock(&mutex);
                    usleep(TURNO_MS * MS);

                } else if (mensaje.int_evento == EVT_MUERTE_ZOMBIE) {
                    printf("Zombie: Fui derrotado por Steve!\n");
                    done = 1;
                } else if (mensaje.int_evento == EVT_INICIO) {
                    printf("Zombie listo para jugar\n");
                } else if (mensaje.int_evento == EVT_FIN) {
                    done = 1;
                }
                break;
                
            case 3: /* Creeper */
                if (mensaje.int_evento == EVT_INICIO) {
                    printf("Creeper listo para jugar\n");
                }
                if (mensaje.int_evento == EVT_ATAQUE_CREEPER) {
                    pthread_mutex_lock(&mutex);
                    resultado = inDevolverNumeroAleatorio(1, 3);
                    printf("Creeper: Ataco a Steve! (resultado: %d)\n", resultado);
                    sprintf(mensaje.char_mensaje, "%d", resultado);
                    enviar_mensaje(id_cola_mensajes, MSG_TABLERO, MSG_JUGADOR + datos->tipo_personaje, EVT_ATAQUE_CREEPER, mensaje.char_mensaje);
                    pthread_mutex_unlock(&mutex);
                    usleep(TURNO_MS * MS);

                } else if (mensaje.int_evento == EVT_MUERTE_CREEPER) {
                    printf("Creeper: Fui derrotado por Steve!\n");
                    done = 1;
                }
                else if (mensaje.int_evento == EVT_FIN) {
                    done = 1;
                }
                break;
        }
    }
    
    pthread_exit(NULL);
}
