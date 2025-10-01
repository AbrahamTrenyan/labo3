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
    int id_semaforo;
    char texto[LARGO];
    /* Inicializar variables */
    memset(texto, 0, LARGO);
    printf("Panel\n");
    printf("Esperando que comiencen los equipos...\n\n");
    /* Obtener semáforo */
    id_semaforo = creo_semaforo(); 
    inicia_semaforo(id_semaforo, 1);
    /*Inicializa el semaforo*/
    while(1)
    {
        /* Verificar si el partido terminó */
        if(inExisteArchivo("partidoTerminado.dat")) {
            printf("=== PARTIDO FINALIZADO ===\n");
            printf("Panel cerrándose...\n");
            exit(0);
        }
        espera_semaforo(id_semaforo);
        procesar_goles(*texto);
        levanta_semaforo(id_semaforo);
        usleep(500 * MS); 
    }
    return 0;
}

