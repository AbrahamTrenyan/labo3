#include "def.h"
#include "funciones.h"
#include "global.h"
#include <string.h>
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
    int *memoria;
    int done;
    Mensaje mensaje;
    DatosLuchador luchadores[NUM_LUCHADORES];
    int i;
    int equipo1_vivo, equipo2_vivo;
    int atacante_id;
    int golpe;
    int daño_realizado;
    int equipo_atacado;
    int inicio;
    int turno_actual;
    int golpe_base_calc;
    int intentos;
    char *arma_nombre;

    /* Inicializo la cola de mensajes y borro los mensajes anteriores */
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);
    
    /* Creo archivo flag indicando que el ring esta inicializado */
    inEscribirArchivo(ARCHIVO_FLAG, "1\n");
    
    /* Creo memoria compartida con la vida inicial */
    memoria = (int *)creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    *memoria = VIDA_INICIAL;
    
    /* Inicializo datos de luchadores en el ring */
    printf("Ingrese nombres (4 luchadores):\n");
    
    for (i = 0; i < NUM_LUCHADORES; i++) {
        printf("[%d] ", i + 1);
        scanf("%s", luchadores[i].nombre);
        luchadores[i].vida = VIDA_INICIAL;
        luchadores[i].id_luchador = i;
        luchadores[i].equipo = (i < NUM_LUCHADORES / 2) ? 1 : 2;
        luchadores[i].id_cola_mensajes = id_cola_mensajes;
    }
    
    srand(time(NULL));
    printf("\n=== COMBATE INICIADO ===\n\n");
    
    done = 0;
    turno_actual = 0;
    
    /* Envío primer turno */
    enviar_mensaje(id_cola_mensajes, MSG_LUCHADOR + turno_actual, MSG_RING, EVT_INICIO, luchadores[turno_actual].nombre);

    while (done == 0) {
        recibir_mensaje(id_cola_mensajes, MSG_RING, &mensaje);
        
        if (mensaje.int_evento == EVT_GOLPE) {
            atacante_id = mensaje.int_rte - MSG_LUCHADOR;
            
            golpe_base_calc = inDevolverNumeroAleatorio(GOLPE_MIN, GOLPE_MAX);
            
            if (strchr(mensaje.char_mensaje, 'c') || strchr(mensaje.char_mensaje, 'C')) {
                arma_nombre = "cuchillo";
                golpe = golpe_base_calc + PUNTOS_CUCHILLO;
            } else {
                arma_nombre = "manopla";
                golpe = golpe_base_calc + PUNTOS_MANOPLA;
            }
            
            daño_realizado = golpe;
            
            equipo_atacado = (atacante_id < 2) ? 2 : 1;
            inicio = (equipo_atacado == 2) ? 2 : 0;
            
            for (i = inicio; i < inicio + 2; i++) {
                luchadores[i].vida -= golpe;
                if (luchadores[i].vida < 0) {
                    luchadores[i].vida = 0;
                }
            }
            
            printf("%s ataca con %s, daño: %d\n", 
                   luchadores[atacante_id].nombre, arma_nombre, daño_realizado);
            
            equipo1_vivo = (luchadores[0].vida > 0) || (luchadores[1].vida > 0);
            equipo2_vivo = (luchadores[2].vida > 0) || (luchadores[3].vida > 0);
            
            if (!equipo1_vivo || !equipo2_vivo) {
                done = 1;
                if (equipo1_vivo) {
                    printf("\n=== EQUIPO 1 GANA ===\n");
                } else {
                    printf("\n=== EQUIPO 2 GANA ===\n");
                }
                for (i = 0; i < NUM_LUCHADORES; i++) {
                    enviar_mensaje(id_cola_mensajes, MSG_LUCHADOR + i, MSG_RING, EVT_FIN, "Fin");
                }
            } else {
                usleep(TURNO_MS * 1000);
                intentos = 0;
                do {
                    turno_actual = (turno_actual + 1) % NUM_LUCHADORES;
                    intentos++;
                } while (luchadores[turno_actual].vida == 0 && intentos < NUM_LUCHADORES);
                
                if (intentos < NUM_LUCHADORES) {
                    enviar_mensaje(id_cola_mensajes, MSG_LUCHADOR + turno_actual, MSG_RING, EVT_GOLPE, luchadores[turno_actual].nombre);
                }
            }
        }
    }
    
    return 0;
}
