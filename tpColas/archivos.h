#ifndef _archivos_h
#define _archivos_h

int abrirArchivo(char *nombreArchivo, char *modo);

void cerrarArchivo(void);

int leerArchivo(char *szBuffer, int sizeOfBuffer);

int escribirArchivo(char *szDatos);


#endif




