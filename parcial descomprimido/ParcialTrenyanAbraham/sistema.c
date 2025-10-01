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
    char sistema;
    char nombreArchivo[LARGO];
    char buffer[LARGO];
    int id_semaforo;
    memset(nombreArchivo, 0, sizeof(nombreArchivo));
    memset(buffer, 0, LARGO);
    obtener_sistema(argc, argv, &sistema);
    printf("Sistema %c: Disponible, esperando bebidas\n", sistema);
    id_semaforo = creo_semaforo();
    while (1)
    {
        espera_semaforo(id_semaforo);
        sprintf(nombreArchivo, "sistema-%c.dat", sistema);
        memset(buffer, 0, sizeof(buffer));
        procesar_bebida(nombreArchivo, sistema, buffer);
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);
    }
    return 0;
}
