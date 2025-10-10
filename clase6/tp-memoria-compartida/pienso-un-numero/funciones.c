#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"
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
    int cantidadTotal = inHasta - inDesde + 1;
    
    if (cantidadTotal <= 0)
    {
        printf("ERROR: Rango inválido [%d, %d]\n", inDesde, inHasta);
        return -1;
    }
    for (posicion = 0; posicion < cantidadTotal; posicion++)
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
    return cantidadTotal;  
}
