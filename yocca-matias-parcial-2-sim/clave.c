#include <stdlib.h>
#include <stdio.h>
#include "clave.h"

key_t clave_crear(int claveBase)
{
    key_t clave;
    clave = ftok("/bin/ls", claveBase);
    if (clave == (key_t)-1)
    {
        printf("No se puede conseguir la clave IPC\n");
        exit(0);
    }
    return clave;
}
