#ifndef _global_h
#define _global_h


#define TRUE 1
#define FALSE 0

#define VERDE 1
#define ROJO 0

#define INTERVALO_PARTIDA 300

#define MENSAJE_A_BANCO 1
#define MENSAJE_A_CAJERO 2

#define E_CONSULTA_SALDO 1
#define E_DEPOSITO 2
#define E_EXTRACCION 3
#define E_RESPUESTA_SALDO 4
#define E_RESPUESTA_SALDO_ERROR 5
#define E_RESPUESTA_DEPOSITO_OK 6
#define E_RESPUESTA_DEPOSITO_ERROR 7
#define E_EXTRACCION_OK 8
#define E_EXTRACCION_ERROR 9


extern FILE *archivo; /* la declaramos para poder usarla a pesar de que no la definimos aca, sino en el global.c
                            , entonces cuando importemos la libreria global.h en los otros archivos, la podemos usar porque todas las funciones usan kla misma 
                                variable global. Tipo todas necesitan acceder al mismo archivo abierto */



#endif


