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
    /*Declaracion de variables*/
    char buffer[LARGO];
    char nombreArchivo[LARGO];
    int i;
    int hayVuelos;
    /*Memset para la primera lectura*/
    memset(buffer, 0, sizeof(buffer));
    memset(nombreArchivo, 0, sizeof(nombreArchivo));
    /*Obtengo semaforo y lo inicalizo el semaforo en verde (1)*/
    id_semaforo = creo_semaforo(); 
    inicia_semaforo(id_semaforo, 1);
    while(1)
    {
        espera_semaforo(id_semaforo);
        printf("Tengo el token\n");
        /*Menu/Logica consumidor*/
        hayVuelos = FALSE;
        /*Reviso todos los archivos de aviones*/
        for(i = 1; i <= CANT_AVIONES; i++)
        {
            memset(nombreArchivo, 0, sizeof(nombreArchivo));
            sprintf(nombreArchivo, "avion%d.dat", i);
            if(inExisteArchivo(nombreArchivo) && inAbrirArchivo(nombreArchivo, "r"))
            {
                if(!hayVuelos)
                {
                    printf("=== PANEL ===\n");
                    hayVuelos = TRUE;
                }
                while(inLeerArchivo(buffer))
                {
                    printf("%s", buffer);
                    memset(buffer, 0, sizeof(buffer));
                }
                voCerrarArchivo();
            }
        }
        
        if(hayVuelos)
        {
            printf("=== FIN DEL MENSAJE ===\n\n");
        }
        /*FIN Menu/Logica consumidor*/
        levanta_semaforo(id_semaforo);
        usleep(TIEMPO_ESPERA * MS);
    }
    return 0;
}

