#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

int id_semaforo;
int contador_lotes = 0;
int vuelos[11];  /* Indices para vuelos 1000-1010 */

void procesar_lote(void)
{
    char linea[MAX_LINEA];
    int vuelo;
    espera_semaforo(id_semaforo);
    if (!inAbrirArchivo("lote.dat", "r")) {
        printf("Error: no se puede abrir lote.dat\n");
        levanta_semaforo(id_semaforo);
        return;
    }
    printf("Procesando reservas del lote:\n");

    while (inLeerArchivo(linea)) {
        /*  extraer el numero de vuelo */
        vuelo = atoi(linea);
        
        printf("Vuelo %d procesado\n", vuelo);
        agregar_pasajero(vuelo);
    }
    
    voCerrarArchivo();
    levanta_semaforo(id_semaforo);
}

void agregar_pasajero(int vuelo)
{
    int indice;
    indice = vuelo - VUELO_MIN;
    if (indice >= 0 && indice < 11) {
        vuelos[indice]++;
    }
}

void mostrar_resumen(void)
{
    int i;
    int vuelo_num;
    
    printf("\n=== RESERVAS ===\n");
    printf("VUELO    PASAJEROS\n");
    printf("-----    ---------\n");
    
    for (i = 0; i < 11; i++) {
        if (vuelos[i] > 0) {
            vuelo_num = VUELO_MIN + i;
            printf("%-8d %d\n", vuelo_num, vuelos[i]);
        }
    }
}

void renombrar_lote(void)
{
    char nuevo_nombre[50];
    
    sprintf(nuevo_nombre, "lote.%03d.dat", contador_lotes);
    
    if (rename("lote.dat", nuevo_nombre) == 0) {
        printf("Lote procesado y renombrado a: %s\n", nuevo_nombre);
        contador_lotes++;
    } else {
        printf("Error: no se pudo renombrar el lote\n");
    }
}
