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
    int id_memoria;
    int *memoria;
    int i;
    pthread_t idHilo[CANT_ANIMALES];
    pthread_attr_t atributos;
    DatosThreadAnimal datos[CANT_ANIMALES];
    
    if (!inExisteArchivo(ARCHIVO_FLAG)) {
        printf("El juego no inicio, debe correr el proceso pista primero\n");
        return 1;
    }

    memoria = (int *)creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    printf("Pasos para llegar a la meta: %d\n", *memoria);
    printf("Preparando animales\n");

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    srand(time(NULL));

    printf("Presione una tecla para iniciar la carrera\n");
    getchar();
    for (i = 0; i < CANT_ANIMALES; i++) {
        datos[i].id_cola_mensajes = id_cola_mensajes;
        datos[i].id_animal = MSG_ANIMAL + i;
        pthread_create(&idHilo[i], &atributos, thread_animal, &datos[i]);
    }
    
    for (i = 0; i < CANT_ANIMALES; i++) {
        pthread_join(idHilo[i], NULL);
    }

    printf("Todos los animales terminaron\n");
    return 0;       
}
