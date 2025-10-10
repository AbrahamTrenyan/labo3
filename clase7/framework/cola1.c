#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include "clave.h"
#include "def.h"
#include "mensajes.h"

#define SOY_PROCESO 1
#define DESTINATARIO 2
#define EVENTO 100

int main(int argc,char *argv[])
{
	int id_cola_mensajes;
	Mensaje mensaje_recibido;
	
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	
	printf("\n---> soy proceso %d, envio un mensaje al proceso %d <---\n",SOY_PROCESO,DESTINATARIO);

	enviar_mensaje(id_cola_mensajes, DESTINATARIO, SOY_PROCESO, EVENTO, "Hola desde cola1");
	
	printf("\n---> soy proceso %d, espero para recibir un mensaje <---\n",SOY_PROCESO);

	recibir_mensaje(id_cola_mensajes, SOY_PROCESO, &mensaje_recibido);
	
	printf("Mensaje recibido de proceso %d: %s\n", mensaje_recibido.int_rte, mensaje_recibido.char_mensaje);
	
	printf("\n---> proceso %d finalizado <---\n",SOY_PROCESO);
	
	return 0;
}
