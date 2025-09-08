#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

void agregar_pasajero(int vuelo)
{
    int indice;
    indice = vuelo - VUELO_MIN;
    vuelos[indice]++;
    printf("Vuelo %d procesado\n", vuelo);
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

