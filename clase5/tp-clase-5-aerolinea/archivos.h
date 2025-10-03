#ifndef _ARCHIVOS
#define _ARCHIVOS
int inAbrirArchivo(char *szNombreArchivo, char *szModo);
void voCerrarArchivo(void);
int inLeerArchivo(char *szBuffer);
int inEscribirArchivo(char *szDatos);
int inExisteArchivo(char *szNombreArchivo);
int inRenombrarArchivo(char *szNombreOriginal, char *szNombreNuevo);
#endif
