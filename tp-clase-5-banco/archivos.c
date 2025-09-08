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
    if (fscanf(ptrFile, "%s", szBuffer) != 1)
        return FALSE;
    return TRUE;
}
int inEscribirArchivo(char *szDatos)
{
    int inRes = 0;
    inRes = fprintf(ptrFile, "%s", szDatos);
    if (inRes < 0)
        return FALSE;
    return TRUE;
}
int inExisteArchivo(char *szNombreArchivo)
{
    FILE *file;
    if ((file = fopen(szNombreArchivo, "r"))) {
        fclose(file);
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
