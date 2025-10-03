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
    int nroPanel;
    char nombreArchivo[LARGO];
    int id_semaforo;
    /*Verifico si paso el argumento y obtengo numero de panel*/
    obtener_numero_panel(argc, argv, &nroPanel);
    printf("Panel %d\n", nroPanel);
    id_semaforo = creo_semaforo();
    while(1)
    {
        espera_semaforo(id_semaforo);
        sprintf(nombreArchivo,"panel%d.dat",nroPanel);
        procesar_panel(nombreArchivo, nroPanel);
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);
    }
    return 0;
}

