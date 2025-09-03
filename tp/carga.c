#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

/* Variables globales externas */
extern int id_semaforo;

int main(int argc, char *argv[])
{
    int vuelo;
    char destino[MAX_DESTINO];
    char nombre[MAX_NOMBRE];
    char linea[MAX_LINEA];
    
    /* Crear semaforo */
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);
    
    printf("=== CARGA ===\n");
    printf("Ingrese vuelos (0 para finalizar):\n");
    
    espera_semaforo(id_semaforo);
    
    if (!inAbrirArchivo("lote.dat", "w")) {
        printf("Error: no se puede crear/abrir el archivo lote.dat\n");
        levanta_semaforo(id_semaforo);
        return 1;
    }
    
    do {
        printf("Vuelo (%d-%d, 0 para finalizar): ", VUELO_MIN, VUELO_MAX);
        scanf("%d", &vuelo);
        
        if (vuelo == VUELO_FIN) {
            break;
        }
        
        if (vuelo < VUELO_MIN || vuelo > VUELO_MAX) {
            printf("Error: vuelo debe estar entre %d y %d\n", VUELO_MIN, VUELO_MAX);
            continue;
        }
        
        printf("Destino: ");
        scanf("%s", destino);
        printf("Nombre del pasajero: ");
        scanf(" %[^\n]", nombre);  /* Lee linea completa con espacios */
        sprintf(linea, "%d|%s|%s\n", vuelo, destino, nombre);
        inEscribirArchivo(linea);
        printf("Reserva agregada exitosamente!\n\n");
        
    } while (vuelo != VUELO_FIN);
    
    voCerrarArchivo();
    levanta_semaforo(id_semaforo);
    printf("Lote creado exitosamente!\n");
    
    return 0;
}
