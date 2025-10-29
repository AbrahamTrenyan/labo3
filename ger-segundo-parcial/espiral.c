#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "colas.h"
#include "def.h"
#include "funciones.h"

int main(int argc, char *argv[]) {

	int id_mosquito, id_cola_mensajes;
	int distancia_mosquito, distancia_espiral = 0;
	int mosquitos_done = 0; 
	int i, done = 0;
	char *buffer;
 	char *tok;
	mensaje msg;

	id_cola_mensajes = creo_id_cola_mensajes();	
	borrar_mensajes(id_cola_mensajes);

	/* Limpio memoria */
        buffer = (char*) malloc(sizeof(char)*(LENGTH+1));
	tok = (char*) malloc(sizeof(char)*(LENGTH+1));
        memset(buffer, 0x00, sizeof(buffer));
	memset(tok, 0x00, sizeof(tok));

	srand(time(NULL));	

	/* Inicializa a los mosquitos */
	for(i=0; i<CANT_MOSQUITOS; i++) {
			enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO+i, MSG_ESPIRAL, EVT_SEGUIR, buffer);
		}

	while(done == 0) {
		
		recibir_mensaje(id_cola_mensajes, MSG_ESPIRAL, &msg);
		memset(buffer, 0x00, sizeof(buffer));

		distancia_espiral += num_random(ESPIRAL_DESDE, ESPIRAL_HASTA);

		printf("\nLa espiral avanzo %d metros", distancia_espiral);

		switch(msg.evento) {
			case EVT_AVANZAR:
				tok = strtok(msg.mensaje, "|");
				id_mosquito = atoi(tok);

				tok = strtok(0, "|");
				distancia_mosquito = atoi(tok);

				if(distancia_mosquito < distancia_espiral) { /* Mosquito fue alcanzado por la espiral */
					enviar_mensaje(id_cola_mensajes, msg.origen, MSG_ESPIRAL, EVT_FIN, "Fin");

					printf("\nID Mosquito %d: Ha sido alcanzado por la espiral a %d metros\n", id_mosquito, distancia_espiral);
					mosquitos_done++;
				} else if(distancia_mosquito >= META) { /* Mosquito se salvo */
					enviar_mensaje(id_cola_mensajes, msg.origen, MSG_ESPIRAL, EVT_FIN, "Fin");

					printf("\nID Mosquito %d: Ha huido de la espiral con %d metros\n", id_mosquito, distancia_mosquito);
					mosquitos_done++;
				} else { /* Mosquito sigue */
					enviar_mensaje(id_cola_mensajes, msg.origen, MSG_ESPIRAL, EVT_SEGUIR, "Seguir");

					printf("\nID Mosquito %d: Lleva %d metros recorridos\n", id_mosquito, distancia_mosquito);
				}

				if(mosquitos_done == CANT_MOSQUITOS) {
					done = 1;
				}
			break;
			}
		sleep(1);
	}

	/*
	for(i=0; i<CANT_MOSQUITOS; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO+i, MSG_ESPIRAL, EVT_FIN, "Fin");
	}
	*/
	free(buffer);

	return 0;	
}

