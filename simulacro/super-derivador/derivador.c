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
    struct producto productos[CANT_MAX_PRODUCTOS]; /*Array de productos*/
    int i;
    int id_semaforo;
    char nombreArchivo[LARGO];
    int nroCaja;
    int cant_productos;
    char nombreProducto[LARGO];
    char texto[LARGO];
    int precioTotal;

    memset(productos, 0, sizeof(productos));
    memset(texto, 0, sizeof(texto));
    memset(nombreArchivo, 0, sizeof(nombreArchivo));
    memset(nombreProducto, 0, sizeof(nombreProducto));
    precioTotal = 0;
    cant_productos = 0;
    nroCaja = 0;
    /*obtengo e inicializo el semaforo*/
	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, 1);
    while(1){
        espera_semaforo(id_semaforo);
        printf("Ingrese el nombre del producto (- para finalizar): ");
		scanf(" %[^\n]",nombreProducto);
        strcpy(productos[cant_productos].descripcion, nombreProducto);
        if(strcmp(nombreProducto,"-")==0)
		{   
			derivar(cant_productos, &nroCaja);
			sprintf(nombreArchivo,"caja%d.dat",nroCaja);
            for(i=0;i<cant_productos;i++){
                sprintf(texto,"%s\t\t$%d\n", productos[i].descripcion, productos[i].precio);
                inEscribirArchivo(nombreArchivo,texto);
            }
            sprintf(texto,"Total: $%d \n", precioTotal);
            inEscribirArchivo(nombreArchivo,texto);
            printf("\nCliente derivado a Caja %d\n", nroCaja);
            printf("Proximo cliente\n");
            /* Vacio el array de productos para el proximo cliente */
            memset(productos, 0, sizeof(productos));
            cant_productos = 0;
            precioTotal = 0;
        }
        else{
            printf("Ingrese el precio del producto: $");
            scanf("%d",&productos[cant_productos].precio);
            precioTotal += productos[cant_productos].precio;
            cant_productos++;
        }
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);
    }
    return 0;   
}
