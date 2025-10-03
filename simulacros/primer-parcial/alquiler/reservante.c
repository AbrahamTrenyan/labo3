#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "archivos.h"
#include "semaforos.h"
#include "clave.h"
#include "def.h"
#include "global.h"
#include "funciones.h"

int main(int argc, char *argv[])
{
    int opcion;
    int nroPropiedad;
    char buffer[LARGO];
    char *token;
    int lineaActual;
    char nombreReservante[LARGO];
    char dniReservante[LARGO];
    
    id_semaforo = creo_semaforo();
    
    while(1)
    {
        espera_semaforo(id_semaforo);
        
        printf("\n1. Consultar\n2. Reservar\nOpcion: ");
        scanf("%d", &opcion);
        
        printf("Numero de propiedad: ");
        scanf("%d", &nroPropiedad);
        
        lineaActual = 0;
        if(inAbrirArchivo(ARCHIVO, "r"))
        {
            while(inLeerArchivo(buffer))
            {
                lineaActual++;
                if(lineaActual == nroPropiedad)
                {
                    if(opcion == 1)
                    {
                        token = strtok(buffer, "\t");
                        printf("Nombre: %s\n", token);
                        token = strtok(NULL, "\t");
                        printf("Precio: %s\n", token);
                        token = strtok(NULL, "\t");
                        printf("Metros: %s\n", token);
                        token = strtok(NULL, "\t");
                        printf("Estado: %s\n", (atoi(strtok(NULL, "\t")) && strtok(NULL, "\t") && atoi(strtok(NULL, "\t"))) ? "Reservada" : "Disponible");
                    }
                    else if(opcion == 2)
                    {
                        printf("Ingrese el numero de propiedad a reservar: ");
                        scanf("%d", &nroPropiedad);
                        printf("Ingrese el nombre del reservante: ");
                        scanf("%s", nombreReservante);
                        printf("Ingrese el DNI del reservante: ");
                        scanf("%s", dniReservante);
                        reservar_propiedad(nroPropiedad, ARCHIVO, nombreReservante, dniReservante);
                    }
                    break;
                }
            }
            voCerrarArchivo();
        }
        levanta_semaforo(id_semaforo);
        usleep(500 * MS);
    }
    return 0;
}

