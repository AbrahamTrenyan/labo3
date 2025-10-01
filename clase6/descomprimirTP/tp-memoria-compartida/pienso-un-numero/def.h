#ifndef _DEF
#define _DEF
#define CANTIDAD 1
#define DESDE 1
#define HASTA 99
#define TRUE 1
#define FALSE 0
#define LARGO 150
#define COMANDO "/bin/ls"     /*Comando conocido para ftok()*/
#define ENTERO 10             /*Entero para ftok()*/
#define ARCHIVO "archivo.dat" /*Nombre del archivo de almacenamiento*/
#define CLAVE_BASE 33         /*Clave base para semaforos y memoria compartida*/
#define MS 1000               /*Multiplicar usleep() por la cantidad de ms requerida*/

typedef struct juego
{
    char nombre_jugador[LARGO];
    int numero_pensado; /* 0=indica sin número, del 1 a 99 número a verificar.*/
    int estado_acierto; /*0=No acierto, 1=acierto.*/
}Juego;

#endif

