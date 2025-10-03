#ifndef _GLOBAL
#define _GLOBAL

extern int id_semaforo;

struct propiedad{
	int id;
	int metros;
	int estado;
	int precio;
	char nombre[255+1];
	char reservante[255+1];
	char dni[255+1];
	char descripcion[255+1];
} Propiedad;
#endif
