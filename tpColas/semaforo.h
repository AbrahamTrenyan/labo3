#ifndef _semaforo_h
#define _semaforo_h

int creoSemaforo(void);

void inicioSemaforo(int id_semaforo, int valor);

void levantaSemaforo(int id_semaforo);

void esperaSemaforo(int id_semaforo);

#endif
