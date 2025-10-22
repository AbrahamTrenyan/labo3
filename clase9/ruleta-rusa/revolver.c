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

void iniciar_juego(int id_cola_mensajes)
{
    int i;
    for (i = 0; i < MAX_CANT_JUGADORES; i++) {
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, 0, EVT_INICIO, "Inicio");
    }
}

void procesar_evento(int id_cola_mensajes, Mensaje mensaje, int numero_elegido_revolver, int *fin)
{
    int numero_elegido_jugador;
    int i;
    int jugador_eliminado;
    
    if (mensaje.int_evento == EVT_DISPARO) {
        numero_elegido_jugador = atoi(mensaje.char_mensaje);
        
        printf("Revolver: Jugador %d eligio posicion %d, bala en posicion %d\n", 
               mensaje.int_rte, numero_elegido_jugador, numero_elegido_revolver);
        
        if (numero_elegido_jugador == numero_elegido_revolver) {
            jugador_eliminado = mensaje.int_rte;
            printf("¡BANG! El jugador %d fue eliminado\n", jugador_eliminado);
            
            for (i = 0; i < MAX_CANT_JUGADORES; i++) {
                sprintf(mensaje.char_mensaje, "%d", jugador_eliminado);
                enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, 0, EVT_FIN, mensaje.char_mensaje);
            }
            *fin = 1;
        } else {
            printf("Click... El jugador %d se salvo\n", mensaje.int_rte);
            sprintf(mensaje.char_mensaje, "%d", mensaje.int_rte);
            enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + mensaje.int_rte, 0, EVT_SALVADO, mensaje.char_mensaje);
        }
    }
    usleep(500000);
}

int main(int argc, char *argv[])
{
    int     numero_elegido_revolver;
    int     id_cola_mensajes;
    int     fin;
    Mensaje mensaje;
    
    /*Inicializo la cola de mensajes y borro los mensajes anteriores*/
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);

    srand(time(NULL));
    numero_elegido_revolver = inDevolverNumeroAleatorio(1, MAX_CANT_JUGADORES);
    printf("Revolver cargado: la bala esta en la posicion %d\n", numero_elegido_revolver);

    printf("Iniciando juego...\n");
    iniciar_juego(id_cola_mensajes);

    fin = 0;
    while (fin == 0) {
        recibir_mensaje(id_cola_mensajes, MSG_REVOLVER, &mensaje);
        procesar_evento(id_cola_mensajes, mensaje, numero_elegido_revolver, &fin);
    }
    
    printf("Juego terminado\n");
    return 0;
}
