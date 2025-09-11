#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "archivos.h"
#include "def.h"
#include "global.h"
FILE *ptrFile; 
int inAbrirArchivo(char *szNombreArchivo, char *szModo)
{
    ptrFile = fopen(szNombreArchivo, szModo);
    if (ptrFile == NULL)
        return FALSE;
    return TRUE;
}
void voCerrarArchivo(void)
{
    fclose(ptrFile);
}
int inLeerArchivo(char *szBuffer)
{
    /*Se puede colocar una validación, sobre la lectura*/
    if (fgets(szBuffer, LARGO, ptrFile) == NULL)
        return FALSE;
    return TRUE;
}
int inEscribirArchivo(char *szNombreArchivo, char *szDatos)
{
    if(inAbrirArchivo(szNombreArchivo,"a"))
	{
		fprintf(ptrFile,"%s",szDatos);
		/*printf("Se escribió en el archivo: %s", szNombreArchivo);*/
		voCerrarArchivo();
        return TRUE;
	}
    else{
        return FALSE;
    }
}
int inExisteArchivo(char *szNombreArchivo)
{
    if ((ptrFile = fopen(szNombreArchivo, "r"))) {
        fclose(ptrFile);
        return TRUE;
    }
    return FALSE;
}

int inRenombrarArchivo(char *szNombreOriginal, char *szNombreNuevo)
{
    if (rename(szNombreOriginal, szNombreNuevo) == 0) {
        return TRUE;
    }
    return FALSE;
}
