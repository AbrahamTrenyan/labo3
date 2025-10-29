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
    int tiros_recibidos;
    Mensaje mensaje;
    int goles;
    int goleadores[CANT_PATEADORES];
    int resultado_tiro;
    int i;
    int done;
    
    tiros_recibidos = 0;
    goles = 0;
    done = 0;
    
    memset(&mensaje, 0, sizeof(mensaje));
    memset(goleadores, 0, sizeof(goleadores));

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);
    inEscribirArchivo(ARCHIVO_FLAG, "1\n");
    printf("Arquero inicializado\n");
    
    srand(time(NULL));
    
    printf("Arquero esperando que inicien los pateadores...\n");
    
    while (done == 0) {
        recibir_mensaje(id_cola_mensajes, MSG_PATEADOR + tiros_recibidos, &mensaje);
        pthread_mutex_lock(&mutex);
        if (mensaje.int_evento == EVT_TIRO) {
            printf("Arquero recibio un tiro del pateador %d\n", tiros_recibidos + 1);
            
            resultado_tiro = inDevolverNumeroAleatorio(DESDE_TIRO, HASTA_TIRO);
            
            
            switch (resultado_tiro) {
                case EVT_GOL:
                    printf("Arquero: GOL del pateador %d\n", tiros_recibidos + 1);
                    enviar_mensaje(id_cola_mensajes, MSG_PATEADOR + OFFSET_RESPUESTA + tiros_recibidos, MSG_ARQUERO, EVT_GOL, "GOL");
                    goles++;
                    goleadores[tiros_recibidos] = 1;
                    break;
                case EVT_PALO:
                    printf("Arquero: PALO del pateador %d\n", tiros_recibidos + 1);
                    enviar_mensaje(id_cola_mensajes, MSG_PATEADOR + OFFSET_RESPUESTA + tiros_recibidos, MSG_ARQUERO, EVT_PALO, "PALO");
                    break;
                case EVT_TRAVESAÑO:
                    printf("Arquero: TRAVESAÑO del pateador %d\n", tiros_recibidos + 1);
                    enviar_mensaje(id_cola_mensajes, MSG_PATEADOR + OFFSET_RESPUESTA + tiros_recibidos, MSG_ARQUERO, EVT_TRAVESAÑO, "TRAVESAÑO");
                    break;
                case EVT_FUERA:
                    printf("Arquero: FUERA del pateador %d\n", tiros_recibidos + 1);
                    enviar_mensaje(id_cola_mensajes, MSG_PATEADOR + OFFSET_RESPUESTA + tiros_recibidos, MSG_ARQUERO, EVT_FUERA, "FUERA");
                    break;
            }
            
            tiros_recibidos++;
            
            if (tiros_recibidos >= CANT_PATEADORES) {
                done = 1;
            }
        }
        pthread_mutex_unlock(&mutex);
        usleep(TURNO_MS * MS);
    }
    
    printf("\n=== Arquero finalizado ===\n");
    printf("Cantidad de goles recibidos: %d\n", goles);
    if(goles > 0) {
        printf("Goleadores: ");
        for (i = 0; i < CANT_PATEADORES; i++) {
            if (goleadores[i] == 1) {
                printf("Pateador %d ", i + 1);
            }
        }
        printf("\n");
    }
    
    return 0;
}
