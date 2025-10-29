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
#define CANT_CAJAS 3
#define MIN_CAJA_1 1
#define MIN_CAJA_2 6
#define MIN_CAJA_3 11
#define MAX_PRODUCTOS 20

#define ARCHIVO_FLAG "flag.dat"
#define PROCESO_INICIALIZADOR "derivador"

struct Mensaje
{
	long long_dest;
	int int_rte;
	int int_evento;
	char char_mensaje[LARGO_MENSAJE];
};

typedef struct {
    char descripcion[50];
    int precio;
} Productos;

/*Estrcutura que maneja el tablero con la informacion de los threads.*/

typedef enum {
    MSG_NADIE,
    MSG_DERIVADOR,
    MSG_CAJA
}Destinos;

typedef enum {
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_ATENDER_CLIENTE,
    EVT_FIN
}Eventos;

typedef struct {
    int id_cola_mensajes;
    int id_caja;
    int id_semaforo;
} DatosCaja;
/*Esta es la estructura que le paso a cada hilo, y se comunica por mensajes*/
#endif
