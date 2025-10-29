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
#include "archivos.h"
#include "memoria.h"
#include "mensajes.h"

int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    int i;
    pthread_t idHilo[CANT_PATEADORES];
    pthread_attr_t atributos;
    DatosThreadPateador datos[CANT_PATEADORES];
    char *resultado;
    int goles;
    char resultados[CANT_PATEADORES][20];
    
    goles = 0;
    
    if (!inExisteArchivo(ARCHIVO_FLAG)) {
        printf("El juego no inicio, debe correr el proceso arquero primero\n");
        return 1;
    }

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    
    pthread_mutex_init(&mutex, NULL);
    
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    srand(time(NULL));

    printf("Presione una tecla para iniciar los penales\n");
    getchar();
    
    for (i = 0; i < CANT_PATEADORES; i++) {
        datos[i].id_cola_mensajes = id_cola_mensajes;
        datos[i].id_pateador = i;
        pthread_create(&idHilo[i], &atributos, thread_pateador, &datos[i]);
    }
    
    for (i = 0; i < CANT_PATEADORES; i++) {
        pthread_join(idHilo[i], (void **)&resultado);
        strcpy(resultados[i], resultado);
        if (strcmp(resultado, "GOL") == 0) {
            goles++;
        }
        free(resultado);
    }

    printf("\n=== Resultados ===\n");
    printf("Cantidad de goles: %d\n\n", goles);
    for (i = 0; i < CANT_PATEADORES; i++) {
        printf("Pateador %d: %s\n", i + 1, resultados[i]);
    }
    
    return 0;       
}
