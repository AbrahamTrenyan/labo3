#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "archivos.h"
#include "def.h"

char szLinea[100 + 1];
int i;

int main(int argc, char *argv[])
{
    memset(szLinea, 0, sizeof(szLinea));

    /* PRODUCCION: Abrir archivo con un solo puntero para escritura */
    if (inAbrirArchivo("producto.txt", "w") == TRUE)
    {
        for (i = 1; i <= 10; i++)
        {
            memset(szLinea, 0, sizeof(szLinea));
            sprintf(szLinea, "PRODUCTO-%02d\n", i);
            if (inEscribirArchivo(szLinea) == FALSE)
            {
                printf("Error al escribir producto %d.\n", i);
                voCerrarArchivo();
                return 1;
            }
        }
        voCerrarArchivo();
    }
    else
    {
        printf("No se pudo abrir el archivo para produccion.\n");
        return 1;
    }

    /* CONSUMO: Abrir el mismo archivo con el mismo puntero para lectura */
    if (inAbrirArchivo("producto.txt", "r") == TRUE)
    {
        while (inLeerArchivo(szLinea) == TRUE)
        {
            printf("%s\n", szLinea);
            memset(szLinea, 0, sizeof(szLinea));
        }
        voCerrarArchivo();
    }
    else
    {
        printf("No se pudo abrir el archivo para consumo.\n");
        return 1;
    }
    return 0;
}
