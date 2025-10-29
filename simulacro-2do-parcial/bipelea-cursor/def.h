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
#define ARMA_CUCHILLO 1
#define ARMA_MANOPLA 2
#define PUNTOS_CUCHILLO 6
#define PUNTOS_MANOPLA 8
#define ACIERTO 1
#define FALLO 2
#define ARCHIVO_FLAG "flag.dat"

#define NUM_LUCHADORES 4
#define EQUIPO_1_L1 0
#define EQUIPO_1_L2 1
#define EQUIPO_2_L1 2
#define EQUIPO_2_L2 3

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
    int equipo;
    int id_luchador;
    int id_cola_mensajes;
} DatosLuchador;

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

#endif
