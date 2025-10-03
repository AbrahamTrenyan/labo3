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
int main(int argc, char *argv[]){
    struct panel Paneles[CANT_PANEL]; /*Array de paneles*/
    int id_semaforo;
    char nombreArchivo[LARGO];
    int nroPanel;
    char mensaje[LARGO];
    char texto[LARGO];
    int opcion;

    memset(Paneles, 0, sizeof(Paneles));
    memset(texto, 0, sizeof(texto));
    memset(nombreArchivo, 0, sizeof(nombreArchivo));
    memset(mensaje, 0, sizeof(mensaje));
    nroPanel = 0;
    /*obtengo e inicializo el semaforo*/
	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, 1);
    while(1){
        espera_semaforo(id_semaforo);
        printf("================================\n");
        printf("1. Leer panel\n");
        printf("2. Escribir panel\n");
        printf("================================\n");
		scanf("%d",&opcion);
        if(opcion==1)
		{   
            printf("Ingrese el numero de panel a leer: \n");
            scanf("%d",&nroPanel);
            if(nroPanel >= 1 && nroPanel <= CANT_PANEL) {
                sprintf(nombreArchivo,"panel%d.dat",nroPanel);
                if(inExisteArchivo(nombreArchivo)) {
                    if(inAbrirArchivo(nombreArchivo, "r")) {
                        if(inLeerArchivo(texto)) {
                            printf("%s", texto);
                        } else {
                            printf("El panel %d está vacío\n", nroPanel);
                        }
                        voCerrarArchivo();
                    } else {
                        printf("Error al abrir el archivo del panel %d\n", nroPanel);
                    }
                } else {
                    printf("El panel %d no existe\n", nroPanel);
                }
                printf("\nPanel %d leido\n", nroPanel);
            } else {
                printf("Número de panel inválido. Debe ser entre 1 y %d\n", CANT_PANEL);
            }
            printf("\n================================\n");
        }
        else if(opcion==2)  {
            printf("Ingrese el numero de panel a escribir: \n");
            scanf("%d",&nroPanel);
            if(nroPanel >= 1 && nroPanel <= CANT_PANEL) {
                printf("Ingrese el mensaje a escribir en el panel: \n");
                scanf(" %[^\n]", mensaje); /* Lee hasta encontrar \n, ignora espacios iniciales */
                sprintf(nombreArchivo,"panel%d.dat",nroPanel);
                strcpy(Paneles[nroPanel-1].mensaje, mensaje);
                strcat(mensaje, "\n");
                /* Sobrescribo el archivo en lugar de hacer append */
                if(inAbrirArchivo(nombreArchivo, "w")) {
                    fprintf(ptrFile, "%s", mensaje);
                    voCerrarArchivo();
                    printf("\nPanel %d escrito correctamente\n", nroPanel);
                } else {
                    printf("\nError al escribir en el panel %d\n", nroPanel);
                }
            } else {
                printf("Número de panel inválido. Debe ser entre 1 y %d\n", CANT_PANEL);
            }
            printf("\n================================\n");
        }
        else{
            printf("La opcion ingresada no es valida\n");
            printf("\n================================");
        }
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);
    }
    return 0;   
}
