#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

void procesar_medicamento(char *nombreArchivo, char sistema)
{
    /* Verifico si existe el archivo y leo su contenido */
    if(inExisteArchivo(nombreArchivo)) {
        if(inAbrirArchivo(nombreArchivo, "r")) {
            memset(buffer, 0, LARGO);
            /* Si hay contenido, leo */
            if(inLeerArchivo(buffer)) {
                printf("Sistema %c\n", sistema);
                printf("Medicamento\tColor\tCantidad\n");
                printf("%s", buffer);
                while(inLeerArchivo(buffer)) {
                    printf("%s", buffer);
                    memset(buffer, 0, LARGO);
                }
                printf("Medicamentos procesados por Sistema %c\n", sistema);
                voCerrarArchivo();
                
            } else {
                voCerrarArchivo();
            }
        } else {
            printf("Error: No se pudo abrir el archivo %s\n", nombreArchivo);
        }
    }
}

void derivar(int cant_productos, char *sistema)
{    
    if(cant_productos == CANT_SISTEMA_A){
        *sistema = 'A'; /* Sistema A */
    }else if(cant_productos == CANT_SISTEMA_B){
        *sistema = 'B'; /* Sistema B */
    }else if(cant_productos == CANT_SISTEMA_C){
        *sistema = 'C'; /* Sistema C */
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
void obtener_sistema(int argc, char *argv[], char *sistema)
{
    if(argc != 2) {
        printf("Ingresa como parametro el  sistema\n");
        exit(1);
    }
    
    if(strcmp(argv[1], "a") != 0 && strcmp(argv[1], "b") != 0 && strcmp(argv[1], "c") != 0){
        printf("El sistema debe ser entre a, b o c.\n");
        exit(1);
    }
    else{
        if(argv[1][0] == 'a') *sistema = 'A';
        else if(argv[1][0] == 'b') *sistema = 'B';
        else if(argv[1][0] == 'c') *sistema = 'C';
    }
}
