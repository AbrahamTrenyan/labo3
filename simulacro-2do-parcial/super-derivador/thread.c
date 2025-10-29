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
#include "semaforos.h"
#include "archivos.h"


void *thread_caja(void *parametro)
{
    DatosCaja *datos;
    int id_cola_mensajes;
    Mensaje mensaje;
    int id_caja;
    int total = 0;
    int done = 0;
    char resumen[LARGO_MENSAJE];
    char nombre_archivo[LARGO_MENSAJE];
    
    datos = (DatosCaja *)parametro;
    id_cola_mensajes = datos->id_cola_mensajes;
    id_caja = datos->id_caja;

    memset(nombre_archivo, 0, sizeof(nombre_archivo));
    sprintf(nombre_archivo, "caja%d.dat", datos->id_caja + 1);
    memset(resumen, 0, sizeof(resumen));
 
    while (done == 0) {
        memset(&mensaje, 0, sizeof(mensaje));
        recibir_mensaje(id_cola_mensajes, MSG_CAJA + id_caja, &mensaje); /*El enviar y recibir mensajes son bloqueantes, por eso estan fuera del mutex*/
        pthread_mutex_lock(&mutex);
        switch (mensaje.int_evento) {
            case EVT_INICIO:
                    printf("Caja %d: Disponible, esperando clientes\n", datos->id_caja + 1);
                    break;
            case EVT_ATENDER_CLIENTE:
                    total += atoi(mensaje.char_mensaje);
                    printf("El precio total del cliente es de %s\n", mensaje.char_mensaje);
                    break;
                case EVT_FIN:
                    /*Hago lo que tengo que hacer para fin*/
                    printf("Caja %d: Terminando\n", datos->id_caja + 1);
                    espera_semaforo( datos->id_semaforo);
                    sprintf(resumen, "El precio total de la caja %d es de %d\n", datos->id_caja +1, total);
                    inEscribirArchivo(nombre_archivo, resumen);
                    levanta_semaforo(datos->id_semaforo);
                    done = 1;
                    break;
                default:
                    printf("Evento no reconocido: %d\n", mensaje.int_evento);
                    break;
            }
        pthread_mutex_unlock(&mutex);
        usleep(TURNO_MS * MS);
        /* enviar_mensaje(id_cola_mensajes, MSG_DERIVADOR, id_caja, EVT_ATENDER_CLIENTE, mensaje.char_mensaje); */
    }
    pthread_exit(NULL);
}
