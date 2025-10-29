#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "colas.h"
#include "def.h"
#include "threads.h"
#include "funciones.h"

int main(int argc, char *argv[]) {

	int i, id_cola_mensajes;	

	tmosquito *datos_thread;
	pthread_t *id_hilo;
	pthread_attr_t atributos;

	id_cola_mensajes = creo_id_cola_mensajes();

	id_hilo = (pthread_t*) malloc(sizeof(pthread_t)*CANT_MOSQUITOS);
	datos_thread = (tmosquito*) malloc(sizeof(tmosquito)*CANT_MOSQUITOS);

	srand(time(NULL));	
	pthread_mutex_init(&mutex, NULL);
	
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
	
	
	for(i=0; i<CANT_MOSQUITOS; i++) {
		datos_thread[i].id = MSG_MOSQUITO+i;
		datos_thread[i].id_cola_mensajes = id_cola_mensajes;

		pthread_create(&id_hilo[i], &atributos, funcionThread, &datos_thread[i]);
	}

	for(i=0; i<CANT_MOSQUITOS; i++) {
		pthread_join(id_hilo[i], NULL);
	}
	

	return 0;	
}

