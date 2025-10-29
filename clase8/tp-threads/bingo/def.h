#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define CANTIDAD_BOLILLAS 99
#define MAX_CANT_JUGADORES 10
#define TAMANIO_CARTON 5


typedef struct {
    int *bolillas;
    int *g_carton_lleno;
    int *cantidad_bolillas_generadas;
    int  numero_jugador;
} Bingo;

#endif
