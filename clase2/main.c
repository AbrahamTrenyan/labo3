#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "funciones.h"
#include "def.h"
#include <string.h>

int main(int argc, char *argv[])
{
    int desde = DESDE;
    int hasta = HASTA;
    int n;
    int numerosAleatorios[CANTIDAD];

    memset(numerosAleatorios, 0, sizeof(numerosAleatorios));

    if (argc == 3)
    {
        desde = atoi(argv[1]);
        hasta = atoi(argv[2]);
    }

    printf("cantidad = %d desde = %d hasta = %d \n", CANTIDAD, desde, hasta);
    srand(time(NULL));

    inDevolverNumeroAleatorioNoRepetitivo(numerosAleatorios, desde, hasta);

    for (n = 0; n < CANTIDAD; n++)
    {
        printf("[%d] = %d\n", n, numerosAleatorios[n]);
    }

    return 0;
}
