#ifndef _DEFINE_H
#define _DEFINE_H

#define ARCHIVO_INICIO "start.dat"
#define SLEEP_TIME 500000
#define CLAVE_BASE 1234
#define LONGITUD_NOMBRE 32
#define CANTIDAD_EQUIPOS 2
#define CANTIDAD_LUCHADORES_POR_EQUIPO 2

#define VIDA_BASE 1200

#define GOLPE_MIN 8
#define GOLPE_MAX 27
#define GOLPE_BONUS_CUCHILLO 6
#define GOLPE_BONUS_MANOPLA 8

#define GANA_EQUIPO_0 0
#define GANA_EQUIPO_1 1
#define SIGUE_EL_JUEGO 2

/* en este caso no uso un enum porque tuve un problema raro que diferia en el valor de cada elemento */
/* al parecer el valor de los enums es undefined behavior en algunos compiladores y no se garantiza que sea el mismo */
/* yo uso este valor como offset de un array para la vida de los luchadores y por lo tanto necesito que comience en*/
#define DEST_ANY 0
#define DEST_ARENA 1
#define DEST_CONTROLADOR 2
#define DEST_LUCHADOR 3

typedef enum evento_t
{
    EVT_INICIO,
    EVT_ATAQUE,
    EVT_FIN
} evento_t;

typedef struct luchador_t
{
    int id;
    int vida;
    char nombre[LONGITUD_NOMBRE];
} luchador_t;

typedef struct parametros_thread_t
{
    int equipo_id;
    int cola_id;
    int vida_base;
    int *done;
} parametros_thread_t;

#endif
