#include <pthread.h>
#include <unistd.h>
#include "threads.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semaforo.h"
#include "unistd.h"
#include "global.h"
#include "archivos.h"
#include "time.h"
#include "funciones.h"
#include "memoria.h"
#include "clave.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "colas.h"

#define DEFAULT 0

typedef enum
{
	MENSAJE_NADIE, /* 0 */
	MENSAJE_TABLERO,
    MENSAJE_CONEJO,
	MENSAJE_GATO,
	MENSAJE_PERRO
} Mensajes;

typedef enum
{
	EVENTO_INICIO, /* 0 */
	EVENTO_NINGUNO, 
	EVENTO_AVANZAR,
	EVENTO_FIN
	

} Eventos;

int main(int argc, char *argv[])
{
	/* int idSemaforo; */
	int idMemoria;
	int idColaMensajes;
	MensajeExtendido mensaje;
	int *memoria = NULL;
	int pasosMeta = 0;
	int juegoTerminado = 0;
	int pasosConejo = 0;
	int pasosGato = 0;
	int pasosPerro = 0;

	memset(&mensaje, 0, sizeof(MensajeExtendido));


	memoria = (int*)creo_memoria(sizeof(int) , &idMemoria, 33);

	*memoria = 117;
	printf("\nPonemos memoria compartida...\n");

	pasosMeta = *memoria;


	srand(time(NULL));

	
	idColaMensajes = creoIdColaMensajes();
	/* liberarColaMensajes(idColaMensajes); */
	borrarMensajesViejos(idColaMensajes);

	activarFlag();

	while(juegoTerminado == 0)
	{

		recibirMensajeExtendido(idColaMensajes, MENSAJE_TABLERO, &mensaje);

		switch(mensaje.int_evento)
		{

			case EVENTO_NINGUNO:

				printf("\nRecibimos evento ninguno...\n");
				break;

			case EVENTO_AVANZAR:

				switch(mensaje.int_rte)
				{

					case MENSAJE_CONEJO:

						pasosConejo = mensaje.n1;
						break;

					case MENSAJE_GATO:

						pasosGato = mensaje.n1;
						break;

					case MENSAJE_PERRO:

						pasosPerro = mensaje.n1;
						break;

				}
				printf("\nPosicion conejo: %d/%d - Posicion gato: %d/%d - Posicion perro: %d/%d\n", 
				pasosConejo, pasosMeta, pasosGato, pasosMeta, pasosPerro, pasosMeta);
				break;

			case EVENTO_FIN:
				juegoTerminado = 1;
				printf("\nFin de la carrera!\n");
				printf("\n-- RESULTADOS --\n");
				printf("\nPosicion conejo: %d/%d - Posicion gato: %d/%d - Posicion perro: %d/%d\n", 
				pasosConejo, pasosMeta, pasosGato, pasosMeta, pasosPerro, pasosMeta);

				if(mensaje.int_rte == MENSAJE_CONEJO)
				{
					printf("\nHa ganado el conejo!\n");
				} else if(mensaje.int_rte == MENSAJE_GATO)
				{
					printf("\nHa ganado el gato\n");
				} else if(mensaje.int_rte == MENSAJE_PERRO)
				{
					printf("\nHa ganado el perro\n");
				}
				break;




		}



	}


	shmdt((char *)memoria);
    shmctl(idMemoria, IPC_RMID, (struct shmid_ds *)NULL);

	return 0;
}
