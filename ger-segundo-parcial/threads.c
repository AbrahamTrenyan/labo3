#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "def.h"
#include "threads.h"
#include "colas.h"
#include "funciones.h"

void *funcionThread(void *param) {

	int id, id_cola_mensajes, avance;
	int done = 0, distancia_recorrida = 0;	
	mensaje msg;
	char buffer[100];
	
	tmosquito *datos_thread = (tmosquito*) param;

	id = datos_thread->id;
	id_cola_mensajes = datos_thread->id_cola_mensajes;

	memset(buffer, 0x00, sizeof(buffer));

	while(done == 0) {
		printf("\n-----------------------------");
		
		memset(buffer, 0x00, sizeof(buffer));
		recibir_mensaje(id_cola_mensajes, id, &msg);
	
		pthread_mutex_lock(&mutex);
		switch(msg.evento) {
			case EVT_SEGUIR:
				avance = num_random(MOSQUITO_DESDE, MOSQUITO_HASTA);
			
				distancia_recorrida += avance;

				printf("\nID Mosquito %d: ha avanzado %d metros", id, avance);
		
				sprintf(buffer, "%d|%d", id, distancia_recorrida);		
				enviar_mensaje(id_cola_mensajes, MSG_ESPIRAL, id, EVT_AVANZAR, buffer);
				
			break;

			case EVT_FIN:
				printf("\nSe ha perdido el rastro del mosquito ID %d\n", id);
				done = 1;
			break;
			default:
				printf("\nSin evento definido");
			break;
		}
		
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	pthread_exit((void*) "Listo");

}
