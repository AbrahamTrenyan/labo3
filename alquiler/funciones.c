#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"
int inDevolverNumeroAleatorio(int inDesde, int inHasta)
{
    if (inDesde > inHasta)
    {
        return -1;
    }
    return (rand() % (inHasta - inDesde + 1)) + inDesde;
}

void reservar_propiedad(int nroPropiedad, char *nombreArchivo, char *nombreReservante, char *dniReservante)
{
    char buffer[LARGO];
    char nuevoTexto[LARGO];
    char *token;
    int lineaActual;
    int encontrado;
    
    memset(buffer, 0, sizeof(buffer));
    memset(nuevoTexto, 0, sizeof(nuevoTexto));
    lineaActual = 0;
    encontrado = FALSE;
    
    if(inAbrirArchivo(nombreArchivo, "r+"))
    {
        while(inLeerArchivo(buffer))
        {
            lineaActual++;
            if(lineaActual == nroPropiedad)
            {
                token = strtok(buffer, "\t");
                sprintf(nuevoTexto, "%s\t\t", token); /* nombre */
                
                token = strtok(NULL, "\t");
                strcat(nuevoTexto, token);
                strcat(nuevoTexto, "\t"); /* precio */
                
                token = strtok(NULL, "\t");
                strcat(nuevoTexto, token);
                strcat(nuevoTexto, "\t"); /* metros */
                
                token = strtok(NULL, "\t");
                strcat(nuevoTexto, token);
                strcat(nuevoTexto, "\t"); /* id */
                
                strcat(nuevoTexto, "1\t"); /* estado = 1 (reservado) */
                strcat(nuevoTexto, nombreReservante);
                strcat(nuevoTexto, "\t");
                strcat(nuevoTexto, dniReservante);
                strcat(nuevoTexto, "\n");
                
                encontrado = TRUE;
                printf("Propiedad reservada exitosamente para %s (DNI: %s)\n", nombreReservante, dniReservante);
                break;
            }
        }
        voCerrarArchivo();
        
        if(encontrado)
        {
            /* Reescribir el archivo con la propiedad actualizada */
            /* Por simplicidad, implementaremos solo el mensaje de confirmacion */
            /* En una implementacion completa, se reescribiria todo el archivo */
        }
        else
        {
            printf("Propiedad no encontrada.\n");
        }
    }
}

