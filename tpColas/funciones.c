#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "funciones.h"

int devolverNumeroAleatorio(int minimo, int maximo)
{
    int numeroAleatorio = 0;


    numeroAleatorio = rand() % (maximo - minimo + 1) + minimo;

    return numeroAleatorio;

}

