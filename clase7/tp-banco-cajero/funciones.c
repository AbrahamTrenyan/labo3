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
