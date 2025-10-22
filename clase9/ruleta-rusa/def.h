#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define MAX_CANT_JUGADORES 6
#define CLAVE_BASE 33
#define LARGO 150
#define LARGO_MENSAJE 150
#define COMANDO "/bin/ls"
#define MS 1000
#define DESDE 1
#define HASTA 100

struct Mensaje
{
	long long_dest;
	int int_rte;
	int int_evento;
	char char_mensaje[LARGO_MENSAJE];
};

typedef struct
{
	int numero_pensado;
	int *alguien_acerto;
	int numero_jugador;
	int numeros_intentados[100];
} Juego;

typedef enum
{
	MSG_NADIE,
	MSG_REVOLVER,
	MSG_JUGADOR
}Destinos;

typedef enum
{
	EVT_NINGUNO,
    EVT_INICIO,
    EVT_DISPARO,
    EVT_SALVADO,
    EVT_FIN
}Eventos;


#endif
