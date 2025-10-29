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

const Posicion tablero[PASOS_TOTALES + 1] = {
    {"Inicio", 0, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Compra caramelos. Pierde $5", -5, 0},
    {"Cuota de la universidad. Pierde $100", -100, 0},
    {"", 0, 0},
    {"Impuestos. Pierde $200", -200, 0},
    {"Cumple años. Recibe $150", 150, 0},
    {"", 0, 0},
    {"Paga la jubilación. Pierde $40", -40, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Entra a la cárcel. Pierde un turno", 0, 1},
    {"Choca el auto. Pierde $400", -400, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Realiza un trabajo. Gana $300", 300, 0},
    {"Le roban. Pierde $600", -600, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Gana la lotería. Gana $800", 800, 0},
    {"", 0, 0},
    {"Vende un sillón. Gana $75", 75, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Pierde la billetera. Pierde $340", -340, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Bitcoin baja. Pierde $120", -120, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Bitcoin sube. Gana $120", 120, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Se compra un auto. Pierde $1000", -1000, 0},
    {"", 0, 0},
    {"Vende el auto. Gana $500", 500, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Se casa. Pierde $400", -400, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Compra comida. Pierde $15", -15, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Vende la tele. Gana $50", 50, 0},
    {"", 0, 0},
    {"Pierde un turno", 0, 1},
    {"Hace otro trabajo. Gana $300", 300, 0},
    {"Recibe $100", 100, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"", 0, 0},
    {"Ultima posición", 0, 0}
};

void procesar_avance(Mensaje mensaje, Jugadores *jugador, int id_cola_mensajes) {
    int pasos;
    int nueva_posicion;
    int monto;
    
    switch (mensaje.int_evento) {
        case EVT_AVANZA:
            pasos = atoi(mensaje.char_mensaje);
            nueva_posicion = jugador->posicion + pasos;
            
            if (nueva_posicion > PASOS_TOTALES) {
                nueva_posicion = PASOS_TOTALES;
            }
            
            jugador->posicion = nueva_posicion;
            printf("%s avanza %d pasos.\nNueva posicion: %d\n", jugador->nombre, pasos, nueva_posicion);
            
            if (tablero[nueva_posicion].mensaje[0] != '\0') {
                printf("%s %s\n", jugador->nombre, tablero[nueva_posicion].mensaje);
            }
            
            monto = tablero[nueva_posicion].monto;
            if (monto != 0) {
                jugador->plata += monto;
                printf("%s Le quedan: $%d\n", jugador->nombre, jugador->plata);
            }
            
            if (tablero[nueva_posicion].pierde_turno == 1) {
                jugador->turno_perdido = 1;
                printf("%s Pierde el proximo turno!\n", jugador->nombre);
            }
            
            if (jugador->plata <= 0) {
                printf("%s Se quedo sin plata! Queda fuera del juego.\n", jugador->nombre);
                enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + jugador->id_jugador, MSG_TABLERO, EVT_FIN, jugador->nombre);
            }
            
            if (jugador->posicion >= PASOS_TOTALES) {
                printf("%s Llego a la meta!\n", jugador->nombre);
            }
            
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
    Jugadores jugadores[MAX_CANT_JUGADORES];
    int ganador = 0;
    int cantidad_jugadores;
    memset(jugadores, 0, sizeof(jugadores));
    memset(&mensaje, 0, sizeof(mensaje));


    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);

    inEscribirArchivo(ARCHIVO_FLAG, "1\n");
    printf("Tablero inicializado\n");
    printf("Esperando cantidad de jugadores del proceso jugadores...\n");
    
    recibir_mensaje(id_cola_mensajes, MSG_TABLERO, &mensaje);
    cantidad_jugadores = atoi(mensaje.char_mensaje);
    printf("Cantidad de jugadores recibida: %d\n", cantidad_jugadores);

    /*Inicializo los jugadores*/
    for (i = 0; i < cantidad_jugadores; i++) {
        sprintf(jugadores[i].nombre, "Jugador %d", i + 1);
        jugadores[i].id_jugador = i;
        jugadores[i].plata = CANT_INICIAL;
        jugadores[i].posicion = 0;
        jugadores[i].turno_perdido = 0;
    }
    
    memoria = (int *)creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    *memoria = CANT_INICIAL;
    printf("Plata inicial compartida en memoria: $%d\n", *memoria);

    srand(time(NULL));
    
    turno = 0;
    while (done == 0) {
        int jugadores_activos;
        int jugador_en_meta;
        
        jugadores_activos = 0;
        jugador_en_meta = 0;

        for (i = 0; i < cantidad_jugadores; i++) {
            if (jugadores[i].plata > 0) {
                jugadores_activos++;
            }
            if (jugadores[i].posicion >= PASOS_TOTALES && jugadores[i].plata > 0) {
                jugador_en_meta = 1;
            }
        }
        
        if (jugadores_activos <= 1 || jugador_en_meta == 1) {
            done = 1;
            break;
        }

        if (jugadores[turno].plata <= 0) {
            turno = (turno + 1) % cantidad_jugadores;
            continue;
        }
        
        printf("------------------------------------\n");
        printf("Turno de %s\n", jugadores[turno].nombre);
        
        if (jugadores[turno].turno_perdido == 1) {
            printf("%s Pierde este turno\n", jugadores[turno].nombre);
            jugadores[turno].turno_perdido = 0;
            turno = (turno + 1) % cantidad_jugadores;
            usleep(TURNO_MS * MS);
            continue;
        }
        
        sprintf(mensaje.char_mensaje, "%d", jugadores[turno].posicion);
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + turno, MSG_TABLERO, EVT_AVANZA, mensaje.char_mensaje);
        recibir_mensaje(id_cola_mensajes, MSG_TABLERO, &mensaje);
        procesar_avance(mensaje, &jugadores[turno], id_cola_mensajes);
        
        turno = (turno + 1) % cantidad_jugadores;
        usleep(TURNO_MS * MS);
    }
    /*Notifico a los jugadores que el juego terminó*/
    for (i = 0; i < cantidad_jugadores; i++) {
        /*Envio el id del ganador para que el jugador pueda saber si gano o perdio*/
        sprintf(mensaje.char_mensaje, "%d", ganador);
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_TABLERO, EVT_FIN, mensaje.char_mensaje);
    }
    
    printf("Termino el juego: \n");
    
    printf("\nResultados finales:\n");
    for (i = 0; i < cantidad_jugadores; i++) {
        printf("%s: Posicion: %d Plata: $%d Estado: %s\n", 
               jugadores[i].nombre, 
               jugadores[i].posicion, 
               jugadores[i].plata,
               jugadores[i].plata > 0 ? "Activo" : "Eliminado");
    }
    
    ganador = 0;
    for (i = 1; i < cantidad_jugadores; i++) {
        if (jugadores[i].plata > 0 && jugadores[ganador].plata <= 0) {
            ganador = i;
        } else if (jugadores[i].plata > 0 && jugadores[ganador].plata > 0) {
            if (jugadores[i].plata > jugadores[ganador].plata) {
                ganador = i;
            }
        }
    }
    
    printf("GANADOR: %s\n", jugadores[ganador].nombre);
;
    
    sleep(1);
    borrar_cola_de_mensajes(id_cola_mensajes);
    return 0;
}
