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
    DatosThreadJugador *datos;
    int id_cola_mensajes;
    Mensaje mensaje;
    int id_corredor;
    int metros;
    int done = 0;
    char nombre[50];

    datos = (DatosThreadJugador *)parametro;
    id_cola_mensajes = datos->id_cola_mensajes;
    id_corredor = datos->id_corredor;

    if (id_corredor == MSG_JUGADOR + 0) {
        strcpy(nombre, "Mosquito 1");
    } else if (id_corredor == MSG_JUGADOR + 1) {
        strcpy(nombre, "Mosquito 2");
    }
    else {
        strcpy(nombre, "Humo");
    }

    while (done == 0) {
        recibir_mensaje(id_cola_mensajes, id_corredor, &mensaje);

        switch (mensaje.int_evento) {
            case EVT_INICIO:
                printf("%s: Listo para la carrera\n", nombre);
                break;

            case EVT_CORRO:
                pthread_mutex_lock(&mutex);
                if (id_corredor < MSG_JUGADOR + CANT_MOSQUITOS) {
                    metros = inDevolverNumeroAleatorio(MIN_METROS_MOSQUITO, MAX_METROS_MOSQUITO);
                } else {
                    metros = inDevolverNumeroAleatorio(MIN_METROS_HUMO, MAX_METROS_HUMO);
                }
                printf("%s: Corro %d metros\n", nombre, metros);
                sprintf(mensaje.char_mensaje, "%d", metros);
                enviar_mensaje(id_cola_mensajes, MSG_TABLERO, id_corredor, EVT_CORRO, mensaje.char_mensaje);
                pthread_mutex_unlock(&mutex);
                usleep(TURNO_MS * MS);
                break;

            case EVT_FIN:
                pthread_mutex_lock(&mutex);
                printf("Finalizo %s: %s\n", nombre, mensaje.char_mensaje);
                done = 1;
                pthread_mutex_unlock(&mutex);
                break;

            default:
                printf("%s: Evento no reconocido: %d\n", nombre, mensaje.int_evento);
                break;
        }
    }
    pthread_exit(NULL);
}
