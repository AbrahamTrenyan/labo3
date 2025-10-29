#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define CLAVE_BASE 33
#define LARGO 150
#define LARGO_MENSAJE 150
#define COMANDO "/bin/ls"
#define MS 1000
#define PASOS_TOTALES 100
#define PASOS_ZOMBIE 20
#define PASOS_CREEPER 45
#define TURNO_MS 400

#define DESDE_PASOS_STEVE 2
#define HASTA_PASOS_STEVE 8
#define DESDE_ATAQUE_CREEPER 1
#define HASTA_ATAQUE_CREEPER 3
#define DESDE_ATAQUE_ZOMBIE 1
#define HASTA_ATAQUE_ZOMBIE 4
#define DESDE_PASOS_PIGLIN 1
#define HASTA_PASOS_PIGLIN 6
#define ARCHIVO_FLAG "flag.dat"


struct Mensaje
{
	long long_dest;
	int int_rte;
	int int_evento;
	char char_mensaje[LARGO_MENSAJE];
};

typedef struct {
    int pasos_steve;
    int pasos_piglin;
    int juego_terminado;
    int ganador; 
    int zombie_encontrado;
    int creeper_encontrado;
} Nether;

typedef enum {
    MSG_NADIE,
    MSG_TABLERO,
    MSG_JUGADOR
}Destinos;

typedef enum {
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_AVANZA_STEVE,
    EVT_AVANZA_PIGLIN,
    EVT_ATAQUE_ZOMBIE,
    EVT_ATAQUE_CREEPER,
    EVT_MUERTE_STEVE,
    EVT_MUERTE_ZOMBIE,
    EVT_MUERTE_CREEPER,
    EVT_VICTORIA_STEVE,
    EVT_VICTORIA_PIGLIN,
    EVT_FIN
}Eventos;


#endif
