#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "global.h"

void *thread_equipo(void *args)
{
    int i, equipo_id, cola_id, vida_base, *done;
    parametros_thread_t *parametros;
    luchador_t luchadores[CANTIDAD_LUCHADORES_POR_EQUIPO];
    mensaje_t mensaje;

    srand(time(NULL));

    parametros = (parametros_thread_t *)args;
    equipo_id = parametros->equipo_id;
    cola_id = parametros->cola_id;
    vida_base = parametros->vida_base;
    done = parametros->done;

    for (i = 0; i < CANTIDAD_LUCHADORES_POR_EQUIPO; i++)
    {
        luchador_inicializar(&luchadores[i], i, vida_base);
    }

    printf("Equipo %d ha entrado en la arena\n", equipo_id);

    while (*done == 0)
    {
        pthread_mutex_lock(&mutex);

        if (*done == 1)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("Equipo %d está luchando\n", equipo_id);

        luchador_atacar(&(luchadores[i]), cola_id);

        pthread_mutex_unlock(&mutex);
        usleep(SLEEP_TIME);
    }

    pthread_exit((void *)"Listo");
}
