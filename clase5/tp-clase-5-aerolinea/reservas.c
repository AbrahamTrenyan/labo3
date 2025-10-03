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

int i;
char linea[MAX_LINEA];
int vuelo;
char nuevo_nombre[50];

int main(int argc, char *argv[])
{
    id_semaforo = creo_semaforo();
    
    /* Limpiar variables */
    memset(linea, 0, sizeof(linea));
    memset(nuevo_nombre, 0, sizeof(nuevo_nombre));
    
    /* Inicializo array de vuelos */
    for (i = 0; i < 11; i++) {
        vuelos[i] = 0;
    }
    
    printf("===  RESERVAS ===\n");
    printf("Esperando lotes\n");
    
    while(1) {
        espera_semaforo(id_semaforo);
        
        if (inExisteArchivo("lote.dat")) {
            printf("Procesando un nuevo lote\n");
            
            if (inAbrirArchivo("lote.dat", "r")) {
                memset(linea, 0, sizeof(linea));
                while (inLeerArchivo(linea)) {
                    vuelo = atoi(linea);
                    agregar_pasajero(vuelo);
                    memset(linea, 0, sizeof(linea));
                }
                voCerrarArchivo();
                
                /* Genero nombre secuencial del archivo */
                memset(nuevo_nombre, 0, sizeof(nuevo_nombre));
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
            }
        }
        
        levanta_semaforo(id_semaforo);
        usleep(TIEMPO_ESPERA);
    }
    
    return 0;
}
