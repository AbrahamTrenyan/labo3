#ifndef _ARCHIVOS_H
#define _ARCHIVOS_H

#include <stdio.h>

FILE *archivo_abrir(char *, char *);
int archivo_leer(FILE *, char *, char *);
int archivo_escribir(FILE *, char *, char *);
int archivo_leer_linea(FILE *, char *, int);
int archivo_cerrar(FILE *);
long archivo_obtener_posicion(FILE *);
int archivo_ir_a_posicion(FILE *, long);

#endif
