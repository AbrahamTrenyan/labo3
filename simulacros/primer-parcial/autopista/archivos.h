#ifndef _ARCHIVOS
#define _ARCHIVOS
#include <stdio.h>
extern FILE *ptrFile;
int inAbrirArchivo(char *szNombreArchivo, char *szModo);
void voCerrarArchivo(void);
int inLeerArchivo(char *szBuffer);
int inEscribirArchivo(char *szNombreArchivo, char *szDatos);
int inExisteArchivo(char *szNombreArchivo);
int inRenombrarArchivo(char *szNombreOriginal, char *szNombreNuevo);
#endif
