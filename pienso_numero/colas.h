#ifndef _COLAS_H
#define _COLAS_H

typedef struct mensaje {

	int destino;
	int origen;
	int evento;
	char mensaje[50];

}mensaje;

int creo_id_cola_mensajes();
int enviar_mensaje(int, long, int, int, char*);
int recibir_mensaje(int,long, mensaje*);
int recibir_mensaje(int,long, mensaje*);
int borrar_mensajes(int);

#endif 
