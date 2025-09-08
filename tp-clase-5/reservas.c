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

int main(int argc, char *argv[])
{
    int i;
    char linea[MAX_LINEA];
    int vuelo;
    char nuevo_nombre[50];
    id_semaforo = creo_semaforo();
    /* Inicializo array de vuelos */
    for (i = 0; i < 11; i++) {
        vuelos[i] = 0;
    }
    printf("===  RESERVAS ===\n");
    printf("Esperando lotes\n");
    
    while (TRUE) {
        if (inExisteArchivo("lote.dat")) {
            printf("Procesando un nuevo lote\n");
            espera_semaforo(id_semaforo);
            if (inAbrirArchivo("lote.dat", "r")) {
                while (inLeerArchivo(linea)) {
                    vuelo = atoi(linea);
                    agregar_pasajero(vuelo);
                }
                voCerrarArchivo();
                levanta_semaforo(id_semaforo);
                /* Genero nombre secuencial del archivo */
                sprintf(nuevo_nombre, "lote.%03d.dat", contador_lotes);
                if (inRenombrarArchivo("lote.dat", nuevo_nombre)) {
                    printf("Lote procesado y renombrado a: %s\n", nuevo_nombre);
                    contador_lotes++;
                } else {
                    printf("Error: no se pudo renombrar el lote\n");
                }
                mostrar_resumen();
                printf("\n");
            } else {
                printf("Error: no se puede abrir lote.dat\n");
                levanta_semaforo(id_semaforo);
            }
        }
        usleep(TIEMPO_ESPERA);
    }
    return 0;
}
