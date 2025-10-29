#ifndef _SEMAFORO_H
#define _SEMAFORO_H

int semaforo_crear(int);
void semaforo_iniciar(int, int);
void semaforo_levantar(int);
void semaforo_esperar(int);

#endif
