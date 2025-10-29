#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "global.h"
#include "def.h"

int carton_lleno = 0;
int control = 0;

typedef struct tipo_jugador {
	int id;
	int *done;
	int respuesta_correcta;
	int *id_ganador;
	int *pensados;
} tjugador;

void *funcionThread(void *param) {

	int id_jugador, nro_pensado, respuesta_correcta;
	
	tjugador *datos_thread = (tjugador*) param;

	id_jugador = datos_thread->id;
	respuesta_correcta = datos_thread->respuesta_correcta;

	printf("\nSoy jugador %d", id_jugador);
	printf("\nNumero a adivinar: %d", datos_thread->respuesta_correcta);
	while(*datos_thread->done == 0) {
		pthread_mutex_lock(&mutex);
		printf("\n-----------------------------");
		printf("\nJugador %d entra al mutex", id_jugador);

		/* Si el numero ya fue pensado pienso en otro */
		nro_pensado = rand()%(PIENSO_HASTA-PIENSO_DESDE)+PIENSO_DESDE;

		while(datos_thread->pensados[nro_pensado] != 0) {
			printf("\nEste numero ya fue pensado: [%d]", nro_pensado);
			nro_pensado = rand()%(PIENSO_HASTA-PIENSO_DESDE)+PIENSO_DESDE;
		}
		
		/* Agrego numero pensado a la lista */
		datos_thread->pensados[nro_pensado] = 1;

		printf("\nPense en: %d", nro_pensado);
		if(nro_pensado == respuesta_correcta) { 
			*datos_thread->done = 1;
			*datos_thread->id_ganador = id_jugador;
		}
				
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	pthread_exit((void*) "Listo");

}

int main(int argc, char *argv[]) {

	int cantidad_jugadores, i;
	int done = 0, id_ganador=0;
	int respuesta_correcta;
	int pensados[100] = {0};	

	tjugador *datos_thread;
	pthread_t *id_hilo;
	pthread_attr_t atributos;
	
	respuesta_correcta = rand()%(PIENSO_HASTA-PIENSO_DESDE)+PIENSO_DESDE;

	if(argc < 1) {
		printf("No se ingreso cantidad jugadores\n");
		exit(1);
	}

	/* Se ingreso la cantidad de jugadores por param */
	if((cantidad_jugadores = atoi(argv[1])) == 0) {
		printf("\nError: No se pudo hacer conversion de param\n");
		exit(1);	
	}

	id_hilo = (pthread_t*) malloc(sizeof(pthread_t)*cantidad_jugadores);
	datos_thread = (tjugador*) malloc(sizeof(tjugador)*cantidad_jugadores);

	srand(time(NULL));	
	pthread_mutex_init(&mutex, NULL);
	
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
	
	
	for(i=0; i<cantidad_jugadores; i++) {
		datos_thread[i].id = i+1;
		datos_thread[i].respuesta_correcta = respuesta_correcta;
		datos_thread[i].done = &done;
		datos_thread[i].id_ganador = &id_ganador;
		datos_thread[i].pensados = pensados;

		pthread_create(&id_hilo[i], &atributos, funcionThread, &datos_thread[i]);
	}

	while(done == 0) {
		pthread_mutex_lock(&mutex);
			printf("\n-----------------------------");
			printf("\nNadie adivino el numero");
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	printf("\n###########################");
	printf("\nID Ganador: %d\n", id_ganador);

	for(i=0; i<cantidad_jugadores; i++) {
		pthread_join(id_hilo[i], NULL);		
		printf("Padre: Ya termino el thread hijo [%d]\n", i+1);	
	}

	return 0;	
}

