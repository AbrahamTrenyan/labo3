#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define CLAVE_BASE 33
#define LARGO_MENSAJE 150
#define COMANDO "/bin/ls"
#define MS 1000
#define TOTAL_METROS 95
#define CANT_MOSQUITOS 2
#define MIN_METROS_MOSQUITO 3
#define MAX_METROS_MOSQUITO 6
#define MIN_METROS_HUMO 1
#define MAX_METROS_HUMO 4

#define TURNO_MS 300

#define ARCHIVO_FLAG "flag.dat"


struct Mensaje
{
	long long_dest;
	int int_rte;
	int int_evento;
	char char_mensaje[LARGO_MENSAJE];
};

typedef struct {
    int cantidad_metros;
    int id_corredor;
} Corredor;
/*Estrcutura que maneja la pista*/

typedef enum {
    MSG_NADIE,
    MSG_TABLERO,     
    MSG_JUGADOR /*El*/
} Destinos;

typedef enum {
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_CORRO,
    EVT_FIN
}Eventos;

typedef struct {
    int id_cola_mensajes;
    int id_corredor;
} DatosThreadJugador;
/*Esta es la estructura que le paso a cada hilo*/
#endif
