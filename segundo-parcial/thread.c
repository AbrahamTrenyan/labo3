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

void procesar_evento(Mensaje mensaje) {
    switch (mensaje.int_evento) {
        case EVT_AVANZA:
            /*Hago lo que tengo que hacer para avanzar*/
            break;
        case EVT_FIN:
            /*Hago lo que tengo que hacer para fin*/
            break;
        default:
            printf("Evento no reconocido: %d\n", mensaje.int_evento);
            break;
    }
}
void *thread_jugador(void *parametro)
{
    DatosJugador *datos;
    int id_cola_mensajes;
    Mensaje mensaje;
    int golpe;
    int arma;
    int equipo_ganador;
    datos = (DatosJugador *)parametro;
    id_cola_mensajes = datos->id_cola_mensajes;
    equipo_ganador = 0;

    while (equipo_ganador == 0) {
        memset(&mensaje, 0, sizeof(mensaje));
        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR + datos->id_jugador, &mensaje); /*El enviar y recibir mensajes son bloqueantes, por eso estan fuera del mutex*/
        pthread_mutex_lock(&mutex); 
        procesar_evento(mensaje);
        pthread_mutex_unlock(&mutex);
        usleep(TURNO_MS * MS);
        enviar_mensaje(id_cola_mensajes, MSG_TABLERO, datos->id_jugador, EVT_AVANZA, mensaje.char_mensaje);
    }
    pthread_exit(NULL);
}
