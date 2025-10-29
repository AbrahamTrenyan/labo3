#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define CLAVE_BASE 33
#define LARGO 150
#define LARGO_MENSAJE 150
#define COMANDO "/bin/ls"
#define MS 1000
/*Constantes de la memoria compartida*/
#define VIDA_INICIAL 1200
/*Delay*/
#define TURNO_MS 400

/*Constantes de la consigna*/
#define CANT_JUGADORES 4
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
} Jugadores;

/*Estrcutura que maneja el tablero con la informacion de los threads.*/

typedef enum {
    MSG_NADIE,
    MSG_TABLERO,
    MSG_JUGADOR
}Destinos;

typedef enum {
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_AVANZA,
    EVT_FIN
}Eventos;

typedef struct {
    int id_cola_mensajes;
    int id_jugador;
    int equipo;
    char nombre[50];
} DatosJugador;
/*Esta es la estructura que le paso a cada hilo, y se comunica por mensajes*/
#endif
