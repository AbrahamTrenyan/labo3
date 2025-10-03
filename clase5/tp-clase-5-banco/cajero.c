#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

int numero_cajero;
int lotes_generados;
int continuar_ejecucion;

void manejar_señal(int señal)
{
    printf("\nCajero %d recibio señal de terminacion. Finalizando...\n", numero_cajero);
    continuar_ejecucion = FALSE;
}

int main(int argc, char *argv[])
{
    int tiempo_espera;
    
    /* Verificar parametros */
    if (argc != 2) {
        printf("Uso: %s <numero_cajero>\n", argv[0]);
        printf("Numero de cajero debe ser 1, 2 o 3\n");
        return 1;
    }
    
    numero_cajero = atoi(argv[1]);
    
    if (numero_cajero < 1 || numero_cajero > CANTIDAD_CAJEROS) {
        printf("Error: numero de cajero debe ser entre 1 y %d\n", CANTIDAD_CAJEROS);
        return 1;
    }
    
    /* Inicializar variables */
    lotes_generados = 0;
    continuar_ejecucion = TRUE;
    
    /* Configurar manejo de señales */
    signal(SIGINT, manejar_señal);
    signal(SIGTERM, manejar_señal);
    
    /* Inicializar semilla aleatoria */
    srand(time(NULL) + numero_cajero);
    
    /* Crear semaforo */
    id_semaforo = creo_semaforo();
    
    printf("=== CAJERO %d ===\n", numero_cajero);
    printf("Simulacion automatica iniciada (max %d lotes)\n", MAX_LOTES_POR_CAJERO);
    printf("Presiona Ctrl+C para terminar antes del limite\n");
    
    while (continuar_ejecucion && lotes_generados < MAX_LOTES_POR_CAJERO) {
        char nombre_archivo[50];
        
        /* Verificar si ya existe un archivo pendiente */
        sprintf(nombre_archivo, "cajero%d.dat", numero_cajero);
        
        if (!inExisteArchivo(nombre_archivo)) {
            /* Esperar tiempo aleatorio entre lotes */
            tiempo_espera = inDevolverNumeroAleatorio(MIN_TIEMPO_ESPERA, MAX_TIEMPO_ESPERA);
            printf("Cajero %d esperando %d microsegundos...\n", numero_cajero, tiempo_espera);
            usleep(tiempo_espera);
            
            /* Generar lote de depositos */
            printf("Cajero %d generando lote %d/%d\n", numero_cajero, lotes_generados + 1, MAX_LOTES_POR_CAJERO);
            espera_semaforo(id_semaforo);
            generar_depositos_aleatorios(numero_cajero);
            levanta_semaforo(id_semaforo);
            lotes_generados++;
        } else {
            /* Si ya existe un archivo, esperar menos tiempo antes de volver a verificar */
            printf("Cajero %d esperando que el tesorero procese el lote pendiente...\n", numero_cajero);
            usleep(500000); /* 500ms */
        }
    }
    
    if (lotes_generados >= MAX_LOTES_POR_CAJERO) {
        printf("Cajero %d: limite de %d lotes alcanzado. Terminando.\n", numero_cajero, MAX_LOTES_POR_CAJERO);
    }
    
    printf("Cajero %d finalizado. Total de lotes generados: %d\n", numero_cajero, lotes_generados);
    return 0;
}
