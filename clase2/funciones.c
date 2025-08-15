#include "stdio.h"
#include "stdlib.h"
#include "def.h"
int inDevolverNumeroAleatorio(int inDesde, int inHasta)
{
    if (inDesde > inHasta)
    {
        return -1;
    }
    return (rand() % (inHasta - inDesde + 1)) + inDesde;
}

int inDevolverNumeroAleatorioNoRepetitivo(int numerosAleatorios[], int inDesde, int inHasta)
{
    int posicion;
    int numero;
    int repetido;
    int i;
    if (CANTIDAD > (inHasta - inDesde + 1))
    {
        printf("ERROR: Solo hay %d números disponibles en el rango [%d, %d], pero se necesitan %d\n", inHasta - inDesde + 1, inDesde, inHasta, CANTIDAD);
        return -1;
    }
    for (posicion = 0; posicion < CANTIDAD; posicion++)
    {
        repetido = 1;
        while (repetido)
        {
            numero = inDevolverNumeroAleatorio(inDesde, inHasta);
            repetido = 0;
            for (i = 0; i < posicion; i++)
            {
                if (numerosAleatorios[i] == numero)
                {
                    repetido = 1;
                    break;
                }
            }
        }
        numerosAleatorios[posicion] = numero;
    }
    return 0;
}
