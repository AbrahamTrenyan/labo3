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

void *thread_pateador(void *parametro)
{
    DatosThreadPateador *datos;
    int id_cola_mensajes;
    Mensaje mensaje;
    int id_pateador;
    char *resultado;
    
    datos = (DatosThreadPateador *)parametro;
    id_cola_mensajes = datos->id_cola_mensajes;
    id_pateador = datos->id_pateador;
    
    resultado = (char *)malloc(20 * sizeof(char));
    memset(&mensaje, 0, sizeof(mensaje));
    
    pthread_mutex_lock(&mutex);
    usleep(TURNO_MS * MS);
    enviar_mensaje(id_cola_mensajes, MSG_PATEADOR + id_pateador, id_pateador, EVT_TIRO, "Tiro");
    pthread_mutex_unlock(&mutex);
    
    recibir_mensaje(id_cola_mensajes, MSG_PATEADOR + OFFSET_RESPUESTA + id_pateador, &mensaje);
    
    switch (mensaje.int_evento) {
        case EVT_GOL:
            strcpy(resultado, "GOL");
            printf("Pateador %d: GOOOOOL\n", id_pateador + 1);
            break;
        case EVT_PALO:
            strcpy(resultado, "PALO");
            printf("Pateador %d: UFFFFF\n", id_pateador + 1);
            break;
        case EVT_TRAVESAÑO:
            strcpy(resultado, "TRAVESAÑO");
            printf("Pateador %d: UFFFFF\n", id_pateador + 1);
            break;
        case EVT_FUERA:
            strcpy(resultado, "FUERA");
            printf("Pateador %d: UFFFFF\n", id_pateador + 1);
            break;
        default:
            strcpy(resultado, "DESCONOCIDO");
            printf("Pateador %d: UFFFFF\n", id_pateador + 1);
            break;
    }
    pthread_exit((void *)resultado);
}
