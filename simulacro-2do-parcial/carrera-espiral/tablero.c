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
    Corredor corredores[CANT_MOSQUITOS + 1];
    int terminados = 0;
    int      avance = 0;
    char nombre[50];
    
    memset(corredores, 0, sizeof(corredores));
    memset(&mensaje, 0, sizeof(mensaje));

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);
    inEscribirArchivo(ARCHIVO_FLAG, "1\n");
    printf("Tablero inicializado\n");
    memoria = creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    *memoria = TOTAL_METROS;
    printf("Distancia a recorrer: %d metros\n", *memoria);
    
    srand(time(NULL));
    
    turno = 0;
    printf("Tablero esperando que inicien los corredores...\n");
    
    while (done == 0) {
        
        /* Verificar si este corredor ya terminó */
        if (corredores[turno].cantidad_metros == -1 || corredores[turno].cantidad_metros >= TOTAL_METROS) {
            /* Este corredor ya terminó, pasar al siguiente */
            turno = (turno + 1) % (CANT_MOSQUITOS + 1);
            continue;
        }
        
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + turno, MSG_TABLERO, EVT_CORRO, "Es tu turno");

        recibir_mensaje(id_cola_mensajes, MSG_TABLERO, &mensaje);
        printf("------------------------------------\n");


        if (mensaje.int_evento == EVT_CORRO) {
            pthread_mutex_lock(&mutex);
            
            avance = atoi(mensaje.char_mensaje);
            
            corredores[turno].cantidad_metros += avance;
            
            if (turno < CANT_MOSQUITOS) {
                sprintf(nombre, "Mosquito %d",  turno + 1);
            } else {
                sprintf(nombre, "Humo");
            }
            printf("%s Avanza %d metros (Total: %d)\n", nombre, 
                avance, 
                corredores[turno].cantidad_metros);
            
            /* Verificar si mosquitos fueron alcanzados por el humo */
            if (turno == CANT_MOSQUITOS) {  /* Es el turno del humo */
                for (i = 0; i < CANT_MOSQUITOS; i++) {
                    if (corredores[i].cantidad_metros > 0 && corredores[i].cantidad_metros < TOTAL_METROS) {
                        if (corredores[i].cantidad_metros <= corredores[CANT_MOSQUITOS].cantidad_metros) {
                            printf("!!! MOSQUITO %d ELIMINADO - alcanzado por el humo !!!\n", i + 1);
                            corredores[i].cantidad_metros = -1;  /* Marcar como eliminado */
                            sprintf(mensaje.char_mensaje, "Eliminado por el humo");
                            enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_TABLERO, EVT_FIN, mensaje.char_mensaje);
                        }
                    }
                }
            }
            
            /* Verificar llegada a meta */
            if (corredores[turno].cantidad_metros >= TOTAL_METROS) {
                if (turno < CANT_MOSQUITOS) {
                    sprintf(mensaje.char_mensaje, "Llegó a la meta");
                    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + turno, MSG_TABLERO, EVT_FIN, mensaje.char_mensaje);
                    printf("El mosquito %d llego a la meta\n", 
                        turno + 1);
                } else {
                    printf("El humo llegó a la meta y elimina a los mosquitos\n");
                    /* Eliminar a los mosquitos */
                    for (i = 0; i < CANT_MOSQUITOS; i++) {
                        corredores[i].cantidad_metros = -1;
                        sprintf(mensaje.char_mensaje, "Eliminado por el humo");
                        printf("El mosquito %d fue eliminado por el humo\n", i + 1);
                        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_TABLERO, EVT_FIN, mensaje.char_mensaje);
                    }
                }
            }
            
            pthread_mutex_unlock(&mutex);
            usleep(TURNO_MS * MS);
        }

        /*Si un jugador gano, paso al siguiente turno*/
        
        turno = (turno + 1) % (CANT_MOSQUITOS + 1);
        
        terminados = 0;
        for (i = 0; i < CANT_MOSQUITOS + 1; i++) {
            if ((corredores[i].cantidad_metros >= TOTAL_METROS) || (corredores[i].cantidad_metros == -1)) {
                terminados++;
            }
        }
        
        if (terminados == CANT_MOSQUITOS) {
            done = 1;
        }
    }
    
    printf("\n===== RESULTADO FINAL =====\n");
    for (i = 0; i < CANT_MOSQUITOS; i++) {
        if (corredores[i].cantidad_metros == -1) {
            printf("Mosquito %d: ELIMINADO\n", i + 1);
        } else if (corredores[i].cantidad_metros >= TOTAL_METROS) {
            printf("Mosquito %d: GANADOR\n", i + 1);
        }
    }
    printf("Humo: %d metros\n", corredores[CANT_MOSQUITOS].cantidad_metros);
    
    /* Enviar mensaje de fin solo al humo */
    enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + CANT_MOSQUITOS, MSG_TABLERO, EVT_FIN, "No llego a la meta");
    
    printf("Juego terminado\n");
    return 0;
}
