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
#define CANT_INICIAL 1000

/*Delay*/
#define TURNO_MS 400

/*Constantes de la consigna*/
#define MIN_AVANCE 0
#define MAX_AVANCE 3
#define PASOS_TOTALES 60
#define MAX_CANT_JUGADORES 4



#define ARCHIVO_FLAG "flag.dat"

typedef struct {
    char nombre[50];
    int plata;
    int posicion;
    int id_jugador;
    int id_cola_mensajes;
    int turno_perdido;
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
    char nombre[50];
} DatosJugador;

typedef struct {
    char mensaje[LARGO_MENSAJE];
    int monto; /*El valor que se le resta o suma*/
    int pierde_turno; /*1 si pierde un turno, 0 si no*/
} Posicion;

#endif
