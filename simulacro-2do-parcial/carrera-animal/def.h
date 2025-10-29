#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define CLAVE_BASE 33
#define LARGO 150
#define LARGO_MENSAJE 150
#define COMANDO "/bin/ls"
#define MS 1000
#define TOTAL_PASOS 117
#define CANT_ANIMALES 3
#define MIN_PASOS_CONEJO 4
#define MAX_PASOS_CONEJO 9
#define MIN_PASOS_GATO 1
#define MAX_PASOS_GATO 10
#define MIN_PASOS_PERRO 3
#define MAX_PASOS_PERRO 8
#define TURNO_MS 500
#define CONEJO "Conejo"
#define GATO "Gato"
#define PERRO "Perro"
#define ARCHIVO_FLAG "flag.dat"


struct Mensaje
{
	long long_dest;
	int int_rte;
	int int_evento;
	char char_mensaje[LARGO_MENSAJE];
};

typedef struct {
    int cantidad_pasos;
    int cantidad_turnos;
    int id_animal;
} Animal;
/*Estrcutura que maneja la pista*/

typedef enum {
    MSG_NADIE,
    MSG_PISTA,     
    MSG_ANIMAL
} Destinos;

typedef enum {
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_CORRO,
    EVT_FIN
}Eventos;

typedef struct {
    int id_cola_mensajes;
    int id_animal;
} DatosThreadAnimal;
/*Esta es la estructura que le paso a cada hilo*/
#endif
