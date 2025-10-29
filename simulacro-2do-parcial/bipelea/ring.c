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
    int golpe = 0;
    Luchadores luchadores[4];
    int equipo_ganador = 0;

    memset(luchadores, 0, sizeof(luchadores));
    memset(&mensaje, 0, sizeof(mensaje));
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);
    
    /*Creo la memoria compartida ANTES del archivo flag*/
    memoria = creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    *memoria = VIDA_INICIAL;
    printf("La cantidad de vida inicial es de %d, se les informa a los hilos por memoria compartida\n", *memoria);
    
    /*Inicializo los luchadores*/
    for (i = 0; i < 4; i++) {
        sprintf(luchadores[i].nombre, "Luchador %d", i);
        luchadores[i].id_jugador = i;
        luchadores[i].equipo = i < 2 ? 1 : 2;
        luchadores[i].vida = VIDA_INICIAL;
    }
    
    srand(time(NULL));
    
    /*Creo el archivo flag DESPUES de inicializar todo y doy tiempo a que se sincronice*/
    usleep(100000);
    inEscribirArchivo(ARCHIVO_FLAG, "1\n");
    printf("Ring inicializado\n");
    printf("------------------------------------\n");
    
    turno = 0;
    while (done == 0) {
        printf("------------------------------------\n");
        printf("Turno del Luchador %d\n", turno);
        
        enviar_mensaje(id_cola_mensajes, MSG_LUCHADOR + turno, MSG_RING, EVT_GOLPE, "Es tu turno");
        
        recibir_mensaje(id_cola_mensajes, MSG_RING, &mensaje);

        if (mensaje.int_evento == EVT_GOLPE) {
            golpe = atoi(mensaje.char_mensaje);
            printf("%s envio un golpe de %d puntos al equipo %d\n", luchadores[mensaje.int_rte].nombre, golpe, luchadores[mensaje.int_rte].equipo == 1 ? 2 : 1);
            
            if (inDevolverNumeroAleatorio(1, 2) == ACIERTO) {
                printf("Golpe acertado\n");
                for (i = 0; i < 4; i++) {
                    if (luchadores[i].equipo != luchadores[mensaje.int_rte].equipo) {
                        luchadores[i].vida -= golpe;
                        if (luchadores[i].vida <= 0) {
                            done = 1;
                            printf("El luchador %s ha sido eliminado\n", luchadores[i].nombre);
                            if (luchadores[i].equipo == 1) {
                                equipo_ganador = 2;
                            } else {
                                equipo_ganador = 1;
                            }
                            sprintf(mensaje.char_mensaje, "%d", equipo_ganador);
                        } else {
                            printf("Vida restante de %s: %d\n", luchadores[i].nombre, luchadores[i].vida);
                        }

                    }
                }
            }
            else {
                printf("%s no acerto el golpe\n", luchadores[mensaje.int_rte].nombre);
                printf("Vida restante de %s: %d\n", luchadores[mensaje.int_rte].nombre, luchadores[mensaje.int_rte].vida);
            }
            usleep(TURNO_MS * MS);
        }

        if (done == 0) {
            /*Sumo 1 y si es 4 vuelvo a 0*/
            turno = (turno + 1) % 4;
        }
    }
    
    for (i = 0; i < 4; i++) {
        enviar_mensaje(id_cola_mensajes, MSG_LUCHADOR + i, MSG_RING, EVT_FIN, mensaje.char_mensaje);
    }
    
    sleep(1);
    printf("Juego terminado\n");
    borrar_cola_de_mensajes(id_cola_mensajes);
    return 0;
}
