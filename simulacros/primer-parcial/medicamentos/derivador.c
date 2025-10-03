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
    struct medicamento medicamentos[CANT_MEDICAMENTOS+1]; /*Array de medicamentos*/
    int i;
    int id_semaforo;
    char nombreArchivo[LARGO];
    char sistema;
    char nombreMedicamento[LARGO];
    char linea[LARGO];
    char texto[LARGO];
    int cantidad;
    memset(medicamentos, 0, sizeof(medicamentos));
    memset(linea, 0, sizeof(linea));
    memset(nombreArchivo, 0, sizeof(nombreArchivo));
    memset(nombreMedicamento, 0, sizeof(nombreMedicamento));
    /*obtengo e inicializo el semaforo*/
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);
    while(1){
        espera_semaforo(id_semaforo);     
        srand(time(NULL));  
        for(i = 0; i < CANT_MEDICAMENTOS; i++) {
            printf("Medicamento %d:\n", i+1);
            printf("Ingrese el nombre del medicamento: ");
            scanf(" %[^\n]", nombreMedicamento);
            strcpy(medicamentos[i].nombre, nombreMedicamento);
            
            printf("Ingrese la cantidad de pastillas (5, 10 o 20): ");
            scanf("%d", &cantidad);
            while(cantidad != 5 && cantidad != 10 && cantidad != 20) {
                printf("Error: La cantidad debe ser 5, 10 o 20. Ingrese nuevamente: ");
                scanf("%d", &cantidad);
            }
            medicamentos[i].cantidad = cantidad;
            printf("Medicamento generado.\n");
        }
        printf("=== PROCESANDO MEDICAMENTOS ===\n");
        for (i = 0; i < CANT_MEDICAMENTOS; i++)
        {
            strcpy(medicamentos[i].color, colores[inDevolverNumeroAleatorio(0, 2)]);
            derivar(medicamentos[i].cantidad, &sistema);
            sprintf(nombreArchivo, "sistema-%c.dat", sistema);
            sprintf(texto, "%s\t\t%s\t\t%d pastillas\n", medicamentos[i].nombre, medicamentos[i].color, medicamentos[i].cantidad);
            inEscribirArchivo(nombreArchivo, texto);
            printf("Medicamento %s derivado a Sistema %c (%d pastillas, color %s)\n", 
                   medicamentos[i].nombre, sistema, medicamentos[i].cantidad, medicamentos[i].color);
        }
        levanta_semaforo(id_semaforo);    
        usleep(1000 * MS);
    }
    return 0;
}
