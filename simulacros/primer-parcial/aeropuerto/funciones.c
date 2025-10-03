#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
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

void obtener_numero_avion(int argc, char *argv[], int *nroAvion)
{
    /*Verifico que se haya ingresado el numero de caja*/
    if(argc != 2) {
        printf("Ingresa como parametro el numero de la avion\n");
        exit(1);
    }
    
    *nroAvion = atoi(argv[1]); 
        if(*nroAvion < 1 || *nroAvion > CANT_AVIONES){
        printf("El nro de avion debe ser entre 1 y %d.\n", CANT_AVIONES);
        exit(1);
    }
}

