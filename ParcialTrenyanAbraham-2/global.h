#ifndef _GLOBAL
#define _GLOBAL

extern int id_semaforo;

struct bebida
{
	char tipo[20];      
	int cantidad;      
	char nombre[255 + 1];
} Bebida;
#endif
