#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

void procesar_panel(char *nombreArchivo, int nroPanel)
{
    static char ultimoMensaje[LARGO] = {0};
    char mensajeActual[LARGO];
    
    /* Inicializo el buffer */
    memset(mensajeActual, 0, sizeof(mensajeActual));
    
    /* Verifico si existe el archivo y leo su contenido */
    if(inExisteArchivo(nombreArchivo)) {
        if(inAbrirArchivo(nombreArchivo, "r")) {
            /* Leo solo la primera línea del archivo */
            if(inLeerArchivo(mensajeActual)) {
                voCerrarArchivo();
                /* Verifico si el mensaje es diferente al último leído */
                if(strcmp(mensajeActual, ultimoMensaje) != 0) {
                    /* Borra la pantalla con secuencias ANSI */
                    printf("\033[2J\033[H");
                    /* Muestro el mensaje */
                    printf("=== PANEL %d ===\n", nroPanel);
                    printf("%s", mensajeActual);
                    printf("=== FIN DEL MENSAJE ===\n\n");
                    /* Guardo el mensaje actual como último leído */
                    strcpy(ultimoMensaje, mensajeActual);
                }
            } else {
                voCerrarArchivo();
            }
        }
    }
}
    void obtener_numero_panel(int argc, char *argv[], int *nroPanel)
{
    /*Verifico que se haya ingresado el numero de caja*/
    if(argc != 2) {
        printf("Ingresa como parametro el numero de panel\n");
        exit(1);
    }
    
    *nroPanel = atoi(argv[1]); 
    if(*nroPanel < 1 || *nroPanel > CANT_PANEL){
        printf("El nro de panel debe ser entre 1 y %d.\n", CANT_PANEL);
        exit(1);
    }
}



