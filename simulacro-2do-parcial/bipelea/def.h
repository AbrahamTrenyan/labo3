#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define CLAVE_BASE 33
#define LARGO 150
#define LARGO_MENSAJE 150
#define COMANDO "/bin/ls"
#define MS 1000
#define VIDA_INICIAL 1200
#define TURNO_MS 400

#define GOLPE_MIN 8
#define GOLPE_MAX 27

#define MANOPLA 1
#define CUCHILLO 2
#define PUNTOS_CUCHILLO 6
#define PUNTOS_MANOPLA 8
#define ACIERTO 1
#define FALLO 2
#define ARCHIVO_FLAG "flag.dat"


struct Mensaje
{
	long long_dest;
	int int_rte;
	int int_evento;
	char char_mensaje[LARGO_MENSAJE];
};

typedef struct {
    char nombre[50];
    int vida;
    int id_jugador;
    int  id_cola_mensajes;
    int equipo;
} Luchadores;
/*Estrcutura que maneja el ring*/
typedef enum {
    MSG_NADIE,
    MSG_RING,
    MSG_LUCHADOR
}Destinos;

typedef enum {
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_GOLPE,
    EVT_FIN
}Eventos;

typedef struct {
    int id_cola_mensajes;
    int id_jugador;
    int equipo;
    char nombre[50];
} DatosLuchador;
/*Esta es la estructura que le paso a cada hilo, la cantidad de vida no la saben, y se comunica por mensajes*/
#endif
