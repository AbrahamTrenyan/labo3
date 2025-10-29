#ifndef _global_h
#define _global_h


#define TRUE 1
#define FALSE 0

#define VERDE 1
#define ROJO 0

#define INTERVALO_PARTIDA 300

#define DEFAULT 0


extern FILE *archivo; /* la declaramos para poder usarla a pesar de que no la definimos aca, sino en el global.c
                            , entonces cuando importemos la libreria global.h en los otros archivos, la podemos usar porque todas las funciones usan kla misma 
                                variable global. Tipo todas necesitan acceder al mismo archivo abierto */



#endif


