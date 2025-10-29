#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "clave.h"
#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "global.h"
#include "thread.h"

int main(int argc, char *argv[])
{
    int i, done, vida_base;
    pthread_attr_t atributos;
    pthread_t *threads;
    parametros_thread_t *parametros;
    int clave, cola_id;
    mensaje_t mensaje;

    clave = clave_crear(CLAVE_BASE);
    cola_id = cola_crear(clave);

    done = 0;

    esperar_inicio(0);

    obtener_vida_base(&vida_base);

    threads = (pthread_t *)malloc(sizeof(pthread_t) * CANTIDAD_EQUIPOS);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&mutex, NULL);

    parametros = (parametros_thread_t *)malloc(sizeof(parametros_thread_t) * CANTIDAD_EQUIPOS);
    for (i = 0; i < CANTIDAD_EQUIPOS; i++)
    {
        parametros[i].equipo_id = i;
        parametros[i].cola_id = cola_id;
        parametros[i].vida_base = vida_base;
        parametros[i].done = &done;
        pthread_create(&threads[i], &atributos, thread_equipo, &parametros[i]);
    }

    cola_recibir(cola_id, DEST_CONTROLADOR, &mensaje);
    printf("El juego ha terminado. Notificando a los equipos...\n");

    done = 1;

    for (i = 0; i < CANTIDAD_EQUIPOS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(parametros);

    return 0;
}
