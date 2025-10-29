#ifndef _THREAD
#define _THREAD

typedef struct {
    int id_cola_mensajes;
    int tipo_personaje; // 0=Steve, 1=Piglin, 2=Zombie, 3=Creeper
} DatosJugador;
void *thread_jugador(void *parametro);

#endif
