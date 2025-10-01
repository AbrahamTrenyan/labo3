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
    struct bebida bebidas[MAX_BEBIDAS]; /*Array de bebidas*/
    int i;
    int cantidadBebidas;
    int id_semaforo;
    char nombreArchivo[LARGO];
    char sistema;
    char nombreBebida[LARGO];
    char linea[LARGO];
    int cantidad;
    int esAlcoholica;
    /*obtengo e inicializo el semaforo*/
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);

    memset(bebidas, 0, sizeof(bebidas));
    memset(linea, 0, sizeof(linea));
    memset(nombreArchivo, 0, sizeof(nombreArchivo));
    memset(nombreBebida, 0, sizeof(nombreBebida));

    while(1){
        espera_semaforo(id_semaforo); 
        printf("Tengo el token\n");    
        srand(time(NULL));
        /* if(inAbrirArchivo("sistema-A.dat", "w")) voCerrarArchivo();
        if(inAbrirArchivo("sistema-B.dat", "w")) voCerrarArchivo();
        if(inAbrirArchivo("sistema-C.dat", "w")) voCerrarArchivo(); limpiar archivos del lote anterior
    */
        
        printf("LOGIARG\n");
        printf("Ingrese las bebidas (escriba '-' para terminar el lote):\n");
        cantidadBebidas = 0;
        while(1) {
            printf("Bebida %d ('-' para terminar): ", cantidadBebidas+1);
            scanf(" %[^\n]", nombreBebida);
            
            if(strcmp(nombreBebida, "-") == 0) {
                break;
            }
            
            strcpy(bebidas[cantidadBebidas].nombre, nombreBebida);
            
            cantidad = inDevolverNumeroAleatorio(1, 3);
            if(cantidad == 1) cantidad = 10;
            else if(cantidad == 2) cantidad = 20;
            else cantidad = 30;
            bebidas[cantidadBebidas].cantidad = cantidad;
            esAlcoholica = inDevolverNumeroAleatorio(1, 2);
            if(esAlcoholica == 1) {
                strcpy(bebidas[cantidadBebidas].tipo, "alcoholica");
            } else {
                strcpy(bebidas[cantidadBebidas].tipo, "no alcoholica");
            }
            
            printf("Bebidas producidas: %s (%s, %d unidades).\n", 
                   bebidas[cantidadBebidas].nombre, bebidas[cantidadBebidas].tipo, bebidas[cantidadBebidas].cantidad);
            cantidadBebidas++;
        }
        
        if(cantidadBebidas > 0) {
            printf("Derivando bebidas\n");
            for (i = 0; i < cantidadBebidas; i++)
            {
                derivar(bebidas[i].cantidad, &sistema);
                sprintf(nombreArchivo, "sistema-%c.dat", sistema);
                sprintf(linea, "%s\t\t%s\t\t%d\n", bebidas[i].nombre, bebidas[i].tipo, bebidas[i].cantidad);
                inEscribirArchivo(nombreArchivo, linea);
                printf("Bebida %s derivada a Sistema %c (%d bebidas, tipo %s)\n", 
                       bebidas[i].nombre, sistema, bebidas[i].cantidad, bebidas[i].tipo);
            }
        } else {
            printf("No se ingresaron bebidas.\n");
            break;
        }
        levanta_semaforo(id_semaforo);    
        usleep(1000 * MS);
    }
    return 0;
}
