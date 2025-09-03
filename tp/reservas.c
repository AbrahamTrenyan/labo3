#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

/* Variables globales externas */
extern int id_semaforo;
extern int contador_lotes;
extern int vuelos[11];

int main(int argc, char *argv[])
{
    int i;
    
    /* Inicializar array de vuelos */
    for (i = 0; i < 11; i++) {
        vuelos[i] = 0;
    }
    
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);
    
    printf("===  RESERVAS ===\n");
    printf("Buscando nuevos lotes\n");
    printf("Ctrl+C para salir\n\n");
    
    while (TRUE) {
        if (inExisteArchivo("lote.dat")) {
            printf("Se detecto un nuevo lote, procesando...\n");
            procesar_lote();
            renombrar_lote();
            mostrar_resumen();
            printf("\n");
        }
        usleep(TIEMPO_ESPERA);
    }
    
    return 0;
}
