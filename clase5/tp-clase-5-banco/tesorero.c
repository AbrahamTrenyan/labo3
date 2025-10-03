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
    char nombre_archivo[50];
    char nuevo_nombre[50];
    int importe;
    int tipo_pago;
    int cajero;
    
    id_semaforo = creo_semaforo();
    
    /* Inicializar contadores */
    for (i = 0; i < CANTIDAD_CAJEROS; i++) {
        contador_lotes[i] = 0;
        cajeros_efectivo[i] = 0;
        cajeros_cheque[i] = 0;
        cajeros_importe_efectivo[i] = 0;
        cajeros_importe_cheque[i] = 0;
    }
    total_efectivo = 0;
    total_cheque = 0;
    total_importe_efectivo = 0;
    total_importe_cheque = 0;
    
    printf("=== TESORERO ===\n");
    printf("Esperando lotes de cajeros cada %d microsegundos\n", ESPERA_TESORERO);
    
    while (TRUE) {
        /* Verificar archivos de cada cajero */
        for (cajero = 1; cajero <= CANTIDAD_CAJEROS; cajero++) {
            sprintf(nombre_archivo, "cajero%d.dat", cajero);
            
            if (inExisteArchivo(nombre_archivo)) {
                printf("Procesando lote del cajero %d\n", cajero);
                espera_semaforo(id_semaforo);
                
                if (inAbrirArchivo(nombre_archivo, "r")) {
                    while (inLeerArchivo(linea)) {
                        if (sscanf(linea, "%d %d", &importe, &tipo_pago) == 2) {
                            procesar_deposito(importe, tipo_pago, cajero);
                        }
                    }
                    voCerrarArchivo();
                    
                    /* Renombrar archivo procesado */
                    sprintf(nuevo_nombre, "cajero%d.%03d.dat", cajero, contador_lotes[cajero - 1]);
                    if (inRenombrarArchivo(nombre_archivo, nuevo_nombre)) {
                        printf("Lote del cajero %d renombrado a: %s\n", cajero, nuevo_nombre);
                        contador_lotes[cajero - 1]++;
                    } else {
                        printf("Error: no se pudo renombrar el lote del cajero %d\n", cajero);
                    }
                    
                    /* Mostrar resumenes */
                    mostrar_resumen_total();
                    for (i = 1; i <= CANTIDAD_CAJEROS; i++) {
                        mostrar_resumen_cajero(i);
                    }
                    printf("========================================\n");
                    
                } else {
                    printf("Error: no se puede abrir %s\n", nombre_archivo);
                }
                
                levanta_semaforo(id_semaforo);
            }
        }
        
        usleep(ESPERA_TESORERO);
    }
    
    return 0;
}
