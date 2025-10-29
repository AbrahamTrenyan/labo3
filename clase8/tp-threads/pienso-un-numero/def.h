#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define MAX_CANT_JUGADORES 10
#define DESDE 1
#define HASTA 10

typedef struct {
    int  numero_pensado;
    int *alguien_acerto;
    int  numero_jugador;
    int  numeros_intentados[11];
} Juego;

#endif
