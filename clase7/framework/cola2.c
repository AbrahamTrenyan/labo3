#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "clave.h"
#include "def.h"
#include "mensajes.h"


#define SOY_PROCESO 2
#define DESTINATARIO 1
#define EVENTO 200


int main(int argc,char *argv[])
{
	int id_cola_mensajes;
	Mensaje mensaje_recibido;
	
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	/*borrar los mensajes pendientes antes de comenzar*/
	borrar_mensajes(id_cola_mensajes);
	
	
	printf("\n---> soy proceso %d, espero para recibir un mensaje <---\n",SOY_PROCESO);

	recibir_mensaje(id_cola_mensajes, SOY_PROCESO, &mensaje_recibido);

	printf("Mensaje recibido de proceso %d: %s\n", mensaje_recibido.int_rte, mensaje_recibido.char_mensaje);

	printf("\n---> soy proceso %d, envio un mensaje al proceso %d <---\n",SOY_PROCESO,DESTINATARIO);
	
	enviar_mensaje(id_cola_mensajes, DESTINATARIO, SOY_PROCESO, EVENTO, "Hola desde cola2");
	
	printf("\n---> proceso %d finalizado <---\n",SOY_PROCESO);
	printf("\n---> borrando cola de mensajes <---\n");
	
	sleep(1);
	borrar_cola_de_mensajes(id_cola_mensajes);

	return 0;
}


