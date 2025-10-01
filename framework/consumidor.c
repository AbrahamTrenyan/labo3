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
    /*Declaracion de variables*/
    int id_semaforo;
    char buffer[LARGO];
    /*Memset*/

    /*Verifico si paso el argumento y obtengo numero de caja*/
    /*Obtengo semaforo*/
    id_semaforo = creo_semaforo(); 
    while(1)
    {
        espera_semaforo(id_semaforo);
        /*Menu/Logica consumidor*/
        inLeerArchivo(ARCHIVO, buffer);
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);
    }
    return 0;
}

