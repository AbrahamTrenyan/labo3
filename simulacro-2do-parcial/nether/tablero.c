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
    int fin;
    Mensaje mensaje;
    int pasos_steve = 0;
    int pasos_piglin = 0;
    int zombie_encontrado = 0;
    int creeper_encontrado = 0;
    int combate_en_curso = 0;
    int i;

    
    /*Inicializo la cola de mensajes y borro los mensajes anteriores*/
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);
    /*Creo archivo flag indicando que el tablero esta inicializado*/
    inEscribirArchivo(ARCHIVO_FLAG, "1\n");
    printf("Tablero inicializado\n");
    /*Creo memoria compartida*/
    memoria = creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    *memoria = PASOS_TOTALES;
    printf("La cantidad de pasos para llegar a la meta es de %d, se les informa a los hilos por memoria compartida\n", *memoria);
    /*Envio mensaje inicio a los jugadores*/
    for (i = 0; i < 4; i++) {
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_TABLERO, EVT_INICIO, "Inicio");
    }
    srand(time(NULL));

    fin = 0;
    /* Comenzar el primer turno */
    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 0, MSG_TABLERO, EVT_AVANZA_STEVE, "0");
    
    while (fin == 0) {
        printf("------------------------------------\n");
        recibir_mensaje(id_cola_mensajes, MSG_TABLERO, &mensaje);
        switch (mensaje.int_evento) {
            case EVT_AVANZA_STEVE:
                pasos_steve += atoi(mensaje.char_mensaje);
                printf("Steve avanza %d pasos (total: %d/100)\n", atoi(mensaje.char_mensaje), pasos_steve);
                
                if (pasos_steve >= PASOS_ZOMBIE && !zombie_encontrado) {
                    zombie_encontrado = 1;
                    combate_en_curso = 1;
                    printf("Steve es atacado por un zombie.\n");
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 2, MSG_TABLERO, EVT_ATAQUE_ZOMBIE, "Ataque zombie");
                    /* NO cambiar turno ni enviar órdenes hasta resolver combate */
                } else if (pasos_steve >= PASOS_CREEPER && !creeper_encontrado) {
                    creeper_encontrado = 1;
                    combate_en_curso = 1;
                    printf("Steve es atacado por un creeper.\n");
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 3, MSG_TABLERO, EVT_ATAQUE_CREEPER, "Ataque creeper");
                    /* NO cambiar turno ni enviar órdenes hasta resolver combate */
                } else if (pasos_steve >= PASOS_TOTALES) {
                    printf("Steve llega al portal. Gano Steve\n");
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 0, MSG_TABLERO, EVT_VICTORIA_STEVE, "Llegaste al portal!");
                    fin = 1;
                } else if (!combate_en_curso) {
                    /* Steve se movió → Automáticamente turno de Piglin */
                    sprintf(mensaje.char_mensaje, "%d", pasos_piglin);
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 1, MSG_TABLERO, EVT_AVANZA_PIGLIN, mensaje.char_mensaje);
                }
                break;
            case EVT_AVANZA_PIGLIN:
                pasos_piglin += atoi(mensaje.char_mensaje);
                printf("Piglin avanza %d pasos (total: %d/100)\n", atoi(mensaje.char_mensaje), pasos_piglin);
                
                if (pasos_piglin >= PASOS_TOTALES) {
                    printf("Piglin cierra el portal! Victoria de Piglin!\n");
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 1, MSG_TABLERO, EVT_VICTORIA_PIGLIN, "Cerraste el portal!");
                    fin = 1;
                } else if (!combate_en_curso) {
                    /* Piglin se movió → Automáticamente turno de Steve */
                    sprintf(mensaje.char_mensaje, "%d", pasos_steve);
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 0, MSG_TABLERO, EVT_AVANZA_STEVE, mensaje.char_mensaje);
                }
                break;
            case EVT_ATAQUE_ZOMBIE:
                combate_en_curso = 0; /* Combate terminado */
                if (atoi(mensaje.char_mensaje) == 4) {
                    /* Zombie mata a Steve */
                    printf("El zombie mato a Steve (resultado: %s/4)\n", mensaje.char_mensaje);
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 0, MSG_TABLERO, EVT_MUERTE_STEVE, "Moriste por el ataque de un zombie");
                    fin = 1;
                } else {
                    /* Steve derrota al zombie */
                    printf("Steve derrota al zombie! (resultado: %s/4)\n", mensaje.char_mensaje);
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 2, MSG_TABLERO, EVT_MUERTE_ZOMBIE, "Fuiste derrotado por Steve");
                    /* Steve sobrevive → Automáticamente turno de Piglin */
                    sprintf(mensaje.char_mensaje, "%d", pasos_steve);
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 1, MSG_TABLERO, EVT_AVANZA_PIGLIN, mensaje.char_mensaje);
                }
                break;
            case EVT_ATAQUE_CREEPER:
                combate_en_curso = 0; /* Combate terminado */
                if (atoi(mensaje.char_mensaje) == 3) {
                    /* Creeper mata a Steve */
                    printf("Creeper mata a Steve! (resultado: %s/3)\n", mensaje.char_mensaje);
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 0, MSG_TABLERO, EVT_MUERTE_STEVE, "Moriste por ataque de un creeper");
                    fin = 1;
                } else {
                    /* Steve derrota al creeper */
                    printf("Steve derrota al creeper! (resultado: %s/3)\n", mensaje.char_mensaje);
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 3, MSG_TABLERO, EVT_MUERTE_CREEPER, "Fuiste derrotado por Steve");
                    /* Steve sobrevive → Automáticamente turno de Piglin */
                    sprintf(mensaje.char_mensaje, "%d", pasos_steve);
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + 1, MSG_TABLERO, EVT_AVANZA_PIGLIN, mensaje.char_mensaje);
                }
                break;
            default:
                printf("Evento no reconocido: %d\n", mensaje.int_evento);
                break;
        }


        usleep(TURNO_MS * MS);
    }
    
    /* Notifico a todos los threads que el juego terminó */
    for (i = 0; i < 4; i++) {
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_TABLERO, EVT_FIN, "Juego terminado");
    }
    
    printf("Juego terminado\n");
    return 0;
}
