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

void procesar_avance(Mensaje mensaje) {
    switch (mensaje.int_evento) {
        case EVT_AVANZA:
            /*Si recibe un avanze, suma los pasos al jugador y muestra*/
            break;
        default:
            printf("Evento no reconocido: %d\n", mensaje.int_evento);
            break;
    }
}

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
    Jugadores jugadores[CANT_JUGADORES];
    int equipo_ganador = 0;

    memset(jugadores, 0, sizeof(jugadores));
    memset(&mensaje, 0, sizeof(mensaje));


    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);


    inEscribirArchivo(ARCHIVO_FLAG, "1\n");
    printf("Tablero inicializado\n");

    /*Inicializo los jugadores*/
    for (i = 0; i < 4; i++) {
        sprintf(jugadores[i].nombre, "Jugador %d", i);
        jugadores[i].id_jugador = i;
    }


    /* memoria = creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    *memoria = VIDA_INICIAL;
    printf("La cantidad de vida inicial es de %d, se les informa a los hilos por memoria compartida\n", *memoria); */


    srand(time(NULL));
    
    for (i = 0; i < CANT_JUGADORES; i++) {
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_TABLERO, EVT_INICIO, jugadores[i].nombre);
    }
    
    turno = 0;
    while (done == 0) {
        printf("------------------------------------\n");
        printf("Turno del Jugador %d\n", turno);
        /*El tablero no utiliza mutex.*/
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + turno, MSG_TABLERO, EVT_AVANZA, "Es tu turno");
        recibir_mensaje(id_cola_mensajes, MSG_TABLERO, &mensaje);
        procesar_avance(mensaje);
        /*En el procesar evento sumo los pasos o resto la vida y muestro lo que paso*/
        if (done == 0) {
            /*Sumo 1 y si es 4 vuelvo a 0*/
            turno = (turno + 1) % CANT_JUGADORES;
        }
    }
    /*Notifico a los jugadores que el juego terminó*/
    for (i = 0; i < CANT_JUGADORES; i++) {
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_TABLERO, EVT_FIN, mensaje.char_mensaje);
    }
    
    sleep(1);
    printf("Juego terminado\n");
    borrar_cola_de_mensajes(id_cola_mensajes);
    return 0;
}
