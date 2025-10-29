#include "def.h"
#include "thread.h"
#include "funciones.h"
#include "global.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *thread_jugador(void *parametro)
{
    Bingo *datos;
    int numero_jugador;
    int carton[TAMANIO_CARTON];
    int cantidad_aciertos;
    int done;
    int i;
    int j;
    int *resultado;

    datos = (Bingo *) parametro;
    numero_jugador = datos->numero_jugador;
    cantidad_aciertos = 0;
    done = 0;
    
    printf("Soy el jugador %d\n", numero_jugador);
    
    memset(carton, 0, sizeof(carton));
    for (i = 0; i < TAMANIO_CARTON; i++) {
        carton[i] = inGenerarNumeroAleatorioNoRepetitivo(carton, i, 1, CANTIDAD_BOLILLAS);
    }
    
    printf("Jugador %d - Carton: ", numero_jugador);
    for (i = 0; i < TAMANIO_CARTON; i++) {
        printf("%02d ", carton[i]);
    }
    printf("\n");
    
    while (done == 0) {
        pthread_mutex_lock(&mutex);
        
        if (g_control != 0) {
            g_control--;
            
            if (*(datos->g_carton_lleno) == 0) {
                for (i = 0; i < TAMANIO_CARTON; i++) {
                    if (carton[i] != 0) {
                        for (j = 0; j < *(datos->cantidad_bolillas_generadas); j++) {
                            if (carton[i] == datos->bolillas[j]) {
                                carton[i] = 0;
                                cantidad_aciertos++;
                                break;
                            }
                        }
                    }
                }
                
                printf("JUGADOR %d ", numero_jugador);
                for (j = 0; j < TAMANIO_CARTON; j++) {
                    printf(" %02d ", carton[j]);
                }
                printf(" Aciertos=%d g_control=%d g_carton_lleno=%d\n", 
                       cantidad_aciertos, g_control, *(datos->g_carton_lleno));
                
                if (cantidad_aciertos == TAMANIO_CARTON) {
                    *(datos->g_carton_lleno) = numero_jugador;
                }
            } else {
                done = 1;
            }
        }
        
        pthread_mutex_unlock(&mutex);
        usleep(10000);
    }
    
    resultado = (int *) malloc(sizeof(int));
    *resultado = cantidad_aciertos;
    pthread_exit((void *) resultado);
}
