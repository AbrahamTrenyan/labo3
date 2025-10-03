#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "archivos.h"
#include "semaforos.h"
#include "clave.h"
#include "def.h"
#include "global.h"
#include "funciones.h"

int main(int argc, char *argv[])
{
    int nroCaja;
    char nombreArchivo[LARGO];
    int id_semaforo;
    char buffer[LARGO];
    /*Verifico si paso el argumento y obtengo numero de caja*/
    obtener_numero_caja(argc, argv, &nroCaja);
    printf("Caja %d: Disponible, esperando clientes\n", nroCaja);
    id_semaforo = creo_semaforo(); 
    while(1)
    {
        espera_semaforo(id_semaforo);
        sprintf(nombreArchivo,"caja%d.dat",nroCaja);
        procesar_pedido(nombreArchivo, nroCaja, buffer);
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);
    }
    return 0;
}

