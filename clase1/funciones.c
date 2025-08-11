#include <stdio.h>
#include <stdlib.h>
#include "def.h"

int devolverNumAleatorio(int desde, int hasta)
{
    return (rand() % (hasta - desde + 1)) + desde;
}

