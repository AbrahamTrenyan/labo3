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

void procesar_evento(Mensaje *mensaje, DatosJugador *datos, int *fin_juego) {
    int pasos;
    int posicion_actual;
    
    switch (mensaje->int_evento) {
        case EVT_AVANZA:
            posicion_actual = atoi(mensaje->char_mensaje);
            pasos = inDevolverNumeroAleatorio(MIN_AVANCE, MAX_AVANCE);
            printf("%s estoy en la posicion %d y avanzo %d pasos\n", datos->nombre, posicion_actual, pasos);
            sprintf(mensaje->char_mensaje, "%d", pasos);
            enviar_mensaje(datos->id_cola_mensajes, MSG_TABLERO, MSG_JUGADOR + datos->id_jugador, EVT_AVANZA, mensaje->char_mensaje);
            break;
        case EVT_FIN:
            printf("%s finalizado\n", datos->nombre);
            if (atoi(mensaje->char_mensaje) == datos->id_jugador) {
                printf("%s: Gane!\n", datos->nombre);
            } else {
                printf("%s: Perdi\n", datos->nombre);
            }
            *fin_juego = 1;
            break;
        default:
            printf("Evento no reconocido: %d\n", mensaje->int_evento);
            break;
    }
}
void *thread_jugador(void *parametro)
{
    DatosJugador *datos;
    int id_cola_mensajes;
    Mensaje mensaje;
    int fin_juego;
    
    datos = (DatosJugador *)parametro;
    id_cola_mensajes = datos->id_cola_mensajes;
    fin_juego = 0;

    while (fin_juego == 0) {
        memset(&mensaje, 0, sizeof(mensaje));
        
        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR + datos->id_jugador, &mensaje);
        pthread_mutex_lock(&mutex);
        procesar_evento(&mensaje, datos, &fin_juego);
        pthread_mutex_unlock(&mutex);
        usleep(TURNO_MS * MS);
    }
    pthread_exit(NULL);
}
