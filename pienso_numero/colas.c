#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "colas.h"
#include "clave.h"
#include "def.h"

int creo_id_cola_mensajes() {

	int id_cola_mensajes = msgget(creo_clave(COMANDO, VALOR_CLAVE), 0600 | IPC_CREAT);

	if(id_cola_mensajes == -1) {
		printf("\nError: Could not create ID for msg queue");
		exit(1);	
	}
	return id_cola_mensajes;
}

int enviar_mensaje(int id_cola_mensaje, long dest, int rte, int evento, char* mensaje_recibido) {

	mensaje msg;

	msg.destino = dest;
	msg.origen = rte;
	msg.evento = evento;
	strcpy(msg.mensaje, mensaje_recibido);

	return msgsnd(id_cola_mensaje,
		(struct msgbuf*)&msg,
		sizeof(msg.origen) + sizeof(msg.evento) + sizeof(msg.mensaje), IPC_NOWAIT);
}

int recibir_mensaje(int id_cola_mensajes,
	long destino, mensaje* rMsg) {

	mensaje msg;
	int result;
	result = msgrcv(id_cola_mensajes,
		(struct msgbuf *)&msg,
		sizeof(msg.origen) + sizeof(msg.evento) + sizeof(msg.mensaje), destino, 0);

	rMsg->destino = msg.destino;
	rMsg->origen = msg.origen;
	rMsg->evento = msg.evento;

	strcpy(rMsg->mensaje, msg.mensaje);	
	return result;
}

int borrar_mensajes(int id_cola_mensajes) {
	mensaje msg;
	int result;

	do {
		result = msgrcv(id_cola_mensajes, (struct msgbuf*)&msg,
			sizeof(msg.origen) + sizeof(msg.evento) + 				sizeof(msg.mensaje), 0, IPC_NOWAIT);
	} while(result>0);

	return result;
} 

