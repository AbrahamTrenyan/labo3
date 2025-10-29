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

void *thread_animal(void *parametro)
{
    DatosThreadAnimal *datos;
    int id_cola_mensajes;
    Mensaje mensaje;
    int id_animal;
    int pasos;
    char *nombre;
    int done = 0;

    datos = (DatosThreadAnimal *)parametro;
    id_cola_mensajes = datos->id_cola_mensajes;
    id_animal = datos->id_animal;

    if (id_animal == MSG_ANIMAL + 0) {
        nombre = CONEJO;
    } else if (id_animal == MSG_ANIMAL + 1) {
        nombre = GATO;
    } else {
        nombre = PERRO;
    }

    while (done == 0) {
        recibir_mensaje(id_cola_mensajes, id_animal, &mensaje);

        switch (mensaje.int_evento) {
            case EVT_INICIO:
                printf("%s: Listo para la carrera\n", nombre);
                break;

            case EVT_CORRO:
                pthread_mutex_lock(&mutex);
                if (id_animal == MSG_ANIMAL + 0) {
                    pasos = inDevolverNumeroAleatorio(MIN_PASOS_CONEJO, MAX_PASOS_CONEJO);
                } else if (id_animal == MSG_ANIMAL + 1) {
                    pasos = inDevolverNumeroAleatorio(MIN_PASOS_GATO, MAX_PASOS_GATO);
                } else {
                    pasos = inDevolverNumeroAleatorio(MIN_PASOS_PERRO, MAX_PASOS_PERRO);
                }
                printf("%s: Corro %d pasos\n", nombre, pasos);
                sprintf(mensaje.char_mensaje, "%d", pasos);
                enviar_mensaje(id_cola_mensajes, MSG_PISTA, id_animal, EVT_CORRO, mensaje.char_mensaje);
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
