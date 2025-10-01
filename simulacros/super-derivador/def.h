/* el def.h se usa para constantes como el finals en lenguajes de alto nivel*/
#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define LARGO 150
#define COMANDO "/bin/ls" /*Comando conocido para ftok()*/
#define ENTERO 10 /*Entero para ftok()*/
#define ARCHIVO "caja.dat" /*Nombre del archivo de almacenamiento*/

#define CANT_CAJAS 3 /*Cantidad de cajas*/
#define MIN_CAJA_1 1 /*Cantidad minima de productos para la caja 1*/
#define MIN_CAJA_2 6 /*Cantidad minima de productos para la caja 2*/
#define MIN_CAJA_3 11 /*Cantidad minima de productos para la caja 3*/
#define CANT_MAX_PRODUCTOS 20 /*Cantidad maxima de productos*/

#define CLAVE_BASE 33 /*Clave base para semaforos*/
#define MS 1000 /*Multiplicar usleep() por la cantidad de ms requerida*/
#endif
