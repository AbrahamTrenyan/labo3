#ifndef _THREAD
#define _THREAD

typedef struct {
    int *vector_tambor;
    int numero_jugador;
} DatosJugador;

void *thread_jugador(void *parametro);

#endif

