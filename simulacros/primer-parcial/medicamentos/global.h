#ifndef _GLOBAL
#define _GLOBAL

extern int id_semaforo;
extern char colores[3][20];

struct medicamento
{
	char color[20];
	int cantidad;
	char nombre[255 + 1];
} Medicamento;
#endif
