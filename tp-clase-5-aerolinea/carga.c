#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

int vuelo;
char destino[MAX_DESTINO];
char nombre[MAX_NOMBRE];
char linea[MAX_LINEA];

int main(int argc, char *argv[])
{
    /* Crear semaforo */
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);
    
    /* Limpiar variables */
    memset(destino, 0, sizeof(destino));
    memset(nombre, 0, sizeof(nombre));
    memset(linea, 0, sizeof(linea));
    
    printf("=== CARGA ===\n");
    printf("Ingrese vuelos (%d para terminar):\n", VUELO_FIN);
    
    while(1) {
        espera_semaforo(id_semaforo);
        
        if (!inAbrirArchivo("lote.dat", "w")) {
            printf("Error: no se puede crear/abrir el archivo lote.dat\n");
            levanta_semaforo(id_semaforo);
            usleep(TIEMPO_ESPERA);
            continue;
        }
        
        do {
            printf("Vuelo (%d-%d, %d para terminar): ", VUELO_MIN, VUELO_MAX, VUELO_FIN);
            scanf("%d", &vuelo);
            
            if (vuelo == VUELO_FIN) {
                voCerrarArchivo();
                printf("Lote creado exitosamente!\n");
                levanta_semaforo(id_semaforo);
                return 0;
            }
            
            if (vuelo < VUELO_MIN || vuelo > VUELO_MAX) {
                printf("Error: vuelo debe estar entre %d y %d\n", VUELO_MIN, VUELO_MAX);
            } else {
                memset(destino, 0, sizeof(destino));
                memset(nombre, 0, sizeof(nombre));
                memset(linea, 0, sizeof(linea));
                
                printf("Destino: ");
                scanf("%s", destino);
                printf("Nombre: ");
                scanf("%s", nombre);
                sprintf(linea, "%d|%s|%s\n", vuelo, destino, nombre);
                inEscribirArchivo(linea);
                printf("Reserva agregada exitosamente!\n\n");
            }
            
        } while (vuelo != VUELO_FIN);
        
        levanta_semaforo(id_semaforo);
        usleep(TIEMPO_ESPERA);
    }
    
    return 0;
}
