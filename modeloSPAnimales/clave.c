#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clave.h"


key_t creoClave(void)
{
    key_t clave;

    clave = ftok("/bin/ls", 33); /* El primer parametro es la ruta de un archivo que sabemos que existe en el sistema
                                        y el segundo parametro es un numero que nosotros elegimos, pero tiene que ser
                                        un numero entre 1 y 255 (un byte) */

    if(clave == (key_t) -1)
    {
        printf("\nNo puedo conseguir clave semaforo, mem compartida, etc.\n");

        exit(0);
    }

    return clave;
}

