#include <string.h>
#include "archivos.h"

FILE *archivo_abrir(char *nombre, char *modo)
{
    FILE *archivo = fopen(nombre, modo);

    if (archivo == NULL)
    {
        printf("No se puede abrir el archivo\n");
    }

    return archivo;
}

int archivo_leer(FILE *archivo, char *formato, char *valor)
{

    int resultado;

    if (archivo == NULL)
    {
        printf("No se puede leer el archivo (no existe o no se ha abierto)\n");
        return 1;
    }

    resultado = fscanf(archivo, formato, valor);

    if (resultado == 0 || resultado == EOF)
    {
        printf("Error al leer el archivo\n");
        return 0;
    }

    return resultado;
}

int archivo_escribir(FILE *archivo, char *formato, char *valor)
{

    if (archivo == NULL)
    {
        printf("No se puede escribir en el archivo (no existe o no se ha abierto)\n");
        return 1;
    }

    fprintf(archivo, formato, valor);

    return 0;
}

int archivo_cerrar(FILE *archivo)
{

    if (archivo == NULL)
    {
        printf("No se puede cerrar el archivo (no existe o no se ha abierto)\n");
        return -1;
    }
    fclose(archivo);
    return 0;
}

int archivo_leer_linea(FILE *archivo, char *cadena, int largo)
{
    if (archivo == NULL)
    {
        printf("No se puede leer la linea del archivo (no existe o no se ha abierto)\n");
        return 0;
    }

    if (fgets(cadena, largo, archivo) == NULL)
    {
        cadena[strcspn(cadena, "\n")] = '\0';
        return EOF;
    }

    return 0;
}

int archivo_ir_a_posicion(FILE *archivo, long posicion)
{
    if (archivo == NULL)
    {
        printf("No se puede mover la posicion del archivo (no existe o no se ha abierto)\n");
        return -1;
    }
    return fseek(archivo, posicion, SEEK_SET);
}
