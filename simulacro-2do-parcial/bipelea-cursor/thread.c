#include "def.h"
#include "thread.h"
#include "funciones.h"
#include "global.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "mensajes.h"

/*La idea es desacoplar los threads, y que el ring sepa la vida que le queda a cada luchador. Entonces los threads solo envian mensajes al ring y el ring se encarga de la logica del combate.*/

void *thread_luchador(void *parametro)
{
    DatosLuchador *datos;
    int id_cola_mensajes;
    Mensaje mensaje;
    int done;
    int golpe_base, arma, golpe_total;
    
    datos = (DatosLuchador *)parametro;
    id_cola_mensajes = datos->id_cola_mensajes;
    
    srand(time(NULL) + datos->id_luchador);
    done = 0;
    
    printf("%s iniciado\n", datos->nombre);
    
    while (!done) {
        recibir_mensaje(id_cola_mensajes, MSG_LUCHADOR + datos->id_luchador, &mensaje);
        
        if (mensaje.int_evento == EVT_INICIO || mensaje.int_evento == EVT_GOLPE) {
            pthread_mutex_lock(&mutex);
            
            golpe_base = inDevolverNumeroAleatorio(GOLPE_MIN, GOLPE_MAX);
            arma = inDevolverNumeroAleatorio(ARMA_CUCHILLO, ARMA_MANOPLA);
            
            if (arma == ARMA_CUCHILLO) {
                golpe_total = golpe_base + PUNTOS_CUCHILLO;
                sprintf(mensaje.char_mensaje, "ataque_cuchillo_%d", golpe_total);
                printf("%s ataca con cuchillo, daño: %d\n", 
                       datos->nombre, golpe_total);
            } else {
                golpe_total = golpe_base + PUNTOS_MANOPLA;
                sprintf(mensaje.char_mensaje, "ataque_manopla_%d", golpe_total);
                printf("%s ataca con manopla, daño: %d\n", 
                       datos->nombre, golpe_total);
            }
            
            enviar_mensaje(id_cola_mensajes, MSG_RING, MSG_LUCHADOR + datos->id_luchador, EVT_GOLPE, mensaje.char_mensaje);
            
            pthread_mutex_unlock(&mutex);
        } else if (mensaje.int_evento == EVT_FIN) {
            done = 1;
            printf("%s finalizado\n", datos->nombre);
        }
    }
    
    pthread_exit(NULL);
}
