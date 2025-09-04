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
