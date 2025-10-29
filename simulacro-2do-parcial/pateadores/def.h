#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define CLAVE_BASE 33
#define LARGO_MENSAJE 150
#define COMANDO "/bin/ls"
#define MS 1000
#define CANT_PATEADORES 5
#define DESDE_TIRO 2
#define HASTA_TIRO 5
#define TURNO_MS 500
#define OFFSET_RESPUESTA 100

#define ARCHIVO_FLAG "flag.dat"


struct Mensaje
{
	long long_dest;
	int int_rte;
	int int_evento;
	char char_mensaje[LARGO_MENSAJE];
};

typedef enum
{
MSG_NADIE, /*0*/
MSG_ARQUERO, /*1*/
MSG_PATEADOR /*2 Cada hilo le suma uno a este define.*/
} Destinos;

typedef enum
{
EVT_NINGUNO, /*0*/
EVT_TIRO, /*1*/
EVT_GOL, /*2*/
EVT_PALO, /*3*/
EVT_TRAVESAÑO, /*4*/    
EVT_FUERA /*5*/
} Eventos;

typedef struct {
    int id_cola_mensajes;
    int id_pateador;
} DatosThreadPateador;
/*Esta es la estructura que le paso a cada hilo*/
#endif
