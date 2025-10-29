#include "def.h"
#include "thread.h"
#include "funciones.h"
#include "global.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mensajes.h"
#include "memoria.h"

void *thread_luchador(void *parametro)
{
    DatosLuchador *datos;
    int id_cola_mensajes;
    Mensaje mensaje;
    int golpe;
    int arma;
    int equipo_ganador;
    datos = (DatosLuchador *)parametro;
    id_cola_mensajes = datos->id_cola_mensajes;
    equipo_ganador = 0;

    while (equipo_ganador == 0) {
        memset(&mensaje, 0, sizeof(mensaje));
        recibir_mensaje(id_cola_mensajes, MSG_LUCHADOR + datos->id_jugador, &mensaje);
        
        switch (mensaje.int_evento) {
            case EVT_INICIO: /*Aca no necesito mutex*/
                printf("%s (equipo %d): Listo para pelear\n", datos->nombre, datos->equipo);
                break;

            case EVT_GOLPE:
                pthread_mutex_lock(&mutex); /*Seccion critica, mi turno*/
                golpe = inDevolverNumeroAleatorio(GOLPE_MIN, GOLPE_MAX);
                arma = inDevolverNumeroAleatorio(MANOPLA, CUCHILLO);
                
                if (arma == CUCHILLO) {
                    golpe += PUNTOS_CUCHILLO;
                    printf("%s: Ataco con cuchillo\n", datos->nombre);
                } else {
                    golpe += PUNTOS_MANOPLA;
                    printf("%s: Ataco con manopla\n", datos->nombre);
                }
                
                printf("%s: Envio golpe de %d puntos\n", datos->nombre, golpe);
                sprintf(mensaje.char_mensaje, "%d", golpe);
                enviar_mensaje(id_cola_mensajes, MSG_RING, datos->id_jugador, EVT_GOLPE, mensaje.char_mensaje);
                pthread_mutex_unlock(&mutex);
                usleep(TURNO_MS * MS);
                break;
                
            case EVT_FIN:
                equipo_ganador = atoi(mensaje.char_mensaje);
                if (equipo_ganador == datos->equipo) {
                    printf("%s: Gane la pelea\n", datos->nombre);
                } else {
                    printf("%s: Perdi la pelea\n", datos->nombre);
                }
                break;
                
            default:
                printf("Evento no reconocido: %d\n", mensaje.int_evento);
                break;
        }
    }
    pthread_exit(NULL);
}
