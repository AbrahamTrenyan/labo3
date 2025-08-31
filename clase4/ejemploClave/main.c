#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "clave.h"

int main(int argc, char *argv[])
{
    key_t clave;

    clave = creo_clave(1);

    printf("Clave obtenida: %d\n", (int)clave);

    return 0;
}

