#include "def.h"
#include "funciones.h"
#include "global.h"
#include "memoria.h"
#include "mensajes.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "archivos.h"

int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    int id_memoria;
    int *memoria = NULL;
    int done = 0;
    int i = 0;
    int turno = 0;
    Mensaje mensaje;
    Animal animales[CANT_ANIMALES];
    int ganadores[CANT_ANIMALES];
    int ganador = -1;
    int turnos_ganador = -1;
    int cantidad_ganadores = 0;
    int hay_ganador = 0;

    memset(ganadores, 0, sizeof(ganadores));
    memset(animales, 0, sizeof(animales));   
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);
    inEscribirArchivo(ARCHIVO_FLAG, "1\n");
    printf("Pista inicializado\n");
    /*Inicializo los animales*/
    for (i = 0; i < CANT_ANIMALES; i++) {
        animales[i].id_animal = MSG_ANIMAL + i;
        animales[i].cantidad_pasos = 0;
        animales[i].cantidad_turnos = 0;
    }
    memoria = creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    *memoria = TOTAL_PASOS;
    printf("La cantidad de pasos para llegar a la meta es de %d, se les informa a los hilos por memoria compartida\n", *memoria);
    srand(time(NULL));

    for (i = 0; i < CANT_ANIMALES; i++) {
        /*Obtengo el nombre del animal del id del animal*/
        sprintf(mensaje.char_mensaje, "%s", animales[i].id_animal == MSG_ANIMAL + 0 ? CONEJO : animales[i].id_animal == MSG_ANIMAL + 1 ? GATO : PERRO);
        enviar_mensaje(id_cola_mensajes, MSG_ANIMAL + i, MSG_PISTA, EVT_INICIO, mensaje.char_mensaje);
    }

    turno = 0;
    printf("Inicialize el proceso animales para comenzar la carrera\n");
    while (done == 0) {
        printf("------------------------------------\n");
        enviar_mensaje(id_cola_mensajes, MSG_ANIMAL + turno, MSG_PISTA, EVT_CORRO, "Es tu turno");
        
        recibir_mensaje(id_cola_mensajes, MSG_PISTA, &mensaje);

        if (mensaje.int_evento == EVT_CORRO) {
            printf("Turno del %s\n", animales[turno].id_animal == MSG_ANIMAL + 0 ? CONEJO : animales[turno].id_animal == MSG_ANIMAL + 1 ? GATO : PERRO);

            pthread_mutex_lock(&mutex);
            animales[turno].cantidad_pasos += atoi(mensaje.char_mensaje);
            printf("El animal %s ha avanzado %d pasos\n", animales[turno].id_animal == MSG_ANIMAL + 0 ? CONEJO : animales[turno].id_animal == MSG_ANIMAL + 1 ? GATO : PERRO, atoi(mensaje.char_mensaje));
            printf("Cantidad de pasos actuales: %d\n", animales[turno].cantidad_pasos);
            animales[turno].cantidad_turnos++;
            if (animales[turno].cantidad_pasos >= TOTAL_PASOS) {
                printf("El animal %s ha llegado a la meta en turno %d\n", animales[turno].id_animal == MSG_ANIMAL + 0 ? CONEJO : animales[turno].id_animal == MSG_ANIMAL + 1 ? GATO : PERRO, animales[turno].cantidad_turnos);
                
                if (ganador == -1) {
                    ganador = turno;
                    turnos_ganador = animales[turno].cantidad_turnos;
                    ganadores[turno] = 1;
                    cantidad_ganadores = 1;
                    hay_ganador = 1;
                } else if (animales[turno].cantidad_turnos == turnos_ganador) {
                    ganadores[turno] = 1;
                    cantidad_ganadores++;
                    printf("EMPATE: %d animales llegaron a la meta con %d turnos\n", cantidad_ganadores, turnos_ganador);
                }
            }
            pthread_mutex_unlock(&mutex);
            usleep(TURNO_MS * MS);
        }
        
        turno = (turno + 1) % CANT_ANIMALES;
        
        if (hay_ganador == 1 && turno == 0) {
            done = 1;
        }
    }
    
    if (cantidad_ganadores == 1) {
        printf("Gano el %s! \n", animales[ganador].id_animal == MSG_ANIMAL + 0 ? CONEJO : animales[ganador].id_animal == MSG_ANIMAL + 1 ? GATO : PERRO);
    } else {
        printf("Empate entre %d animales \n", cantidad_ganadores);
        for (i = 0; i < CANT_ANIMALES; i++) {
            if (ganadores[i] == 1) {
                printf("El %s empato\n", animales[i].id_animal == MSG_ANIMAL + 0 ? CONEJO : animales[i].id_animal == MSG_ANIMAL + 1 ? GATO : PERRO);
            }
        }
    }
    
    for (i = 0; i < CANT_ANIMALES; i++) {
        if (ganadores[i] == 1) {
            if (cantidad_ganadores == 1) {
                enviar_mensaje(id_cola_mensajes, MSG_ANIMAL + i, MSG_PISTA, EVT_FIN, "Ganador");
            } else {
                enviar_mensaje(id_cola_mensajes, MSG_ANIMAL + i, MSG_PISTA, EVT_FIN, "Empate");
            }
        } else {
            enviar_mensaje(id_cola_mensajes, MSG_ANIMAL + i, MSG_PISTA, EVT_FIN, "Perdedor");
        }
    }
    
    printf("Juego terminado\n");
    return 0;
}
