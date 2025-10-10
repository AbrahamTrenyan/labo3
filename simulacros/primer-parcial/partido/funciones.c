#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

void obtener_equipo(int argc, char *argv[], int *equipo)
{
    /*Verifico que se haya ingresado el numero de equipo*/
    if(argc != 2) {
        printf("Ingresa como parametro el numero de la equipo\n");
        exit(1);
    }
    *equipo = atoi(argv[1]); 
    if(*equipo < 1 || *equipo >2){
        printf("El nro de equipo debe ser entre 1 o 2.\n");
        exit(1);
    }
}

int inDevolverNumeroAleatorio(int inDesde, int inHasta)
{
    if (inDesde > inHasta)
    {
        return -1;
    }
    return (rand() % (inHasta - inDesde + 1)) + inDesde;
}



void procesar_goles(char *texto)
{
    /* Muestra si empezo el partido*/
    if(inExisteArchivo(ARCHIVO_1) || inExisteArchivo(ARCHIVO_2)) {
        /* Resetear contadores */
        goles_equipo1 = 0;
        goles_equipo2 = 0;
        /* Procesar archivo equipo1.dat */
        if(inExisteArchivo(ARCHIVO_1)) {
            if(inAbrirArchivo(ARCHIVO_1, "r")) {
                memset(texto, 0, LARGO);
                while(inLeerArchivo(texto)) {
                    if(atoi(texto) == 1) {
                        goles_equipo1++;
                    }
                }
                voCerrarArchivo();
            }
        }
        /* Procesar archivo equipo2.dat */
        if(inExisteArchivo(ARCHIVO_2)) {
            if(inAbrirArchivo(ARCHIVO_2, "r")) {
                memset(texto, 0, LARGO);
                while(inLeerArchivo(texto)) {
                    if(atoi(texto) == 1) {
                        goles_equipo2++;
                    }
                }
                voCerrarArchivo();
            }
        }
        
        /* Mostrar información del partido */
        printf("=== PANEL DEL PARTIDO ===\n");
        printf("Equipo 1: %d goles\n", goles_equipo1);
        printf("Equipo 2: %d goles\n", goles_equipo2);
        
        /* Verificar si alguien ganó */
        if(goles_equipo1 >= MAX_GOLES) {
            printf("¡GANÓ EL EQUIPO 1!\n");
            printf("Partido terminado\n");
            if(inAbrirArchivo("partidoTerminado.dat", "w")) {
                inEscribirArchivo("partidoTerminado.dat", "TERMINADO\n");
                voCerrarArchivo();
            }
        } else if(goles_equipo2 >= MAX_GOLES) {
            printf("¡GANÓ EL EQUIPO 2!\n");
            printf("Partido terminado\n");
            if(inAbrirArchivo("partidoTerminado.dat", "w")) {
                inEscribirArchivo("partidoTerminado.dat", "TERMINADO\n");
                voCerrarArchivo();
            }
        }
        printf("==========================\n\n");
    }
}
