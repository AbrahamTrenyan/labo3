#ifndef _THREADS_H
#define _THREADS_H

typedef struct tipo_mosquito {
	int id;
	int id_cola_mensajes;
} tmosquito;

pthread_mutex_t mutex;

void *funcionThread(void *param);

#endif
