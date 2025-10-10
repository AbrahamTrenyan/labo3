#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "archivos.h"
#include "global.h"


int abrirArchivo(char *nombreArchivo, char *modo)
{
    archivo = fopen(nombreArchivo, modo);

    if(archivo == NULL)
    {
        return FALSE;
    }

    return TRUE;
}

void cerrarArchivo(void) /* supuestamente en ANSI C es necesario, si no pasamos parametros, pasar void para que compile  */
{
    fclose(archivo);
}

int leerArchivo(char *szBuffer, int sizeOfBuffer)
{
    /*
    if(fscanf(archivo, "%s", szBuffer) == 1) 
    {
        return TRUE;
    } else
    {
        return FALSE; 
    }
    */
    if (fgets(szBuffer, sizeOfBuffer, archivo) != NULL) 
    {
        return TRUE;
    } else
    {
        return FALSE; 
    }
    



}

int escribirArchivo(char *szDatos)
{
    int inRes = 0;
    inRes = fprintf(archivo, "%s\n", szDatos); /* la funcion fprintf devuelve la cantidad de caracteres escritos (creo)
                                                    y si devuelve un valor negativo, es porque hubo error, por eso confirmamos con el if 
                                                    y devolvemos false si hubo un error y true si salió todo ok */
    if(inRes < 0)
    {
        return FALSE;
    }
    return TRUE;
}
