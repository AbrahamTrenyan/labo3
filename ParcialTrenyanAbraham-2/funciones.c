#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

void procesar_bebida(char *nombreArchivo, char sistema, char *buffer)
{
    /* Verifico si existe el archivo y leo su contenido */
    if(inExisteArchivo(nombreArchivo)) {
        if(inAbrirArchivo(nombreArchivo, "r")) {
            memset(buffer, 0, LARGO);
            /* Si hay contenido, lo proceso */
            if(inLeerArchivo(buffer)) {
                printf("Sistema %c\n", sistema);         
                printf("Bebida\t\tTipo\t\tCantidad\n");
                printf("%s", buffer);
                while(inLeerArchivo(buffer)) {
                    printf("%s", buffer);
                    memset(buffer, 0, LARGO);
                }
                voCerrarArchivo();
                printf("Bebidas procesadas por Sistema %c\n", sistema);
                
                /* Vaciar el archivo después de procesarlo para evitar relecturas */
                if(inAbrirArchivo(nombreArchivo, "w")) {
                    voCerrarArchivo();
                }
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
        *sistema = 'A'; 
    }else if(cant_productos == CANT_SISTEMA_B){
        *sistema = 'B'; 
    }else if(cant_productos == CANT_SISTEMA_C){
        *sistema = 'C'; 
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
        printf("Ingresa como parametro el sistema\n");
        exit(1);
    }
    
    if(strcmp(argv[1], "a") != 0 && strcmp(argv[1], "b") != 0 && strcmp(argv[1], "c") != 0 &&
       strcmp(argv[1], "A") != 0 && strcmp(argv[1], "B") != 0 && strcmp(argv[1], "C") != 0){
        printf("El sistema debe ser a, b, c, A, B o C.\n");
        exit(1);
    }
    else{
        if(argv[1][0] == 'a' || argv[1][0] == 'A') *sistema = 'A';
        else if(argv[1][0] == 'b' || argv[1][0] == 'B') *sistema = 'B';
        else if(argv[1][0] == 'c' || argv[1][0] == 'C') *sistema = 'C';
    }
}
