#include "def.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "funciones.h"

int inDevolverNumeroAleatorio(int inDesde, int inHasta)
{
    if (inDesde > inHasta) {
        return -1;
    }
    return (rand() % (inHasta - inDesde + 1)) + inDesde;
}

void inDevolverNumeroAleatorioNoRepetitivo(int numerosAleatorios[], int inDesde, int inHasta)
{
    int posicion;
    int numero;
    int repetido;
    int i;
    int cantidad;
    
    cantidad = inHasta - inDesde + 1;

    if (cantidad <= 0) {
        printf("El rango es inválido [%d, %d]\n", inDesde, inHasta);
        return;
    }
    for (posicion = 0; posicion < cantidad; posicion++) {
        repetido = 1;
        while (repetido) {
            numero = inDevolverNumeroAleatorio(inDesde, inHasta);
            repetido = 0;
            for (i = 0; i < posicion; i++) {
                if (numerosAleatorios[i] == numero) {
                    repetido = 1;
                    break;
                }
            }
        }
        numerosAleatorios[posicion] = numero;
    }
}
void derivar(int cant_productos, int *nroCaja)
{
    if(cant_productos == 0){
        printf("No hay productos ingresados\n");
    }
    else if(cant_productos > MIN_CAJA_1 && cant_productos <= MIN_CAJA_2){
        *nroCaja = 0;
    }
    else if(cant_productos >= MIN_CAJA_2 && cant_productos <= MIN_CAJA_3){
        *nroCaja = 1;
    }
    else if(cant_productos >= MIN_CAJA_3 && cant_productos <= MAX_PRODUCTOS){
        *nroCaja = 2;
    }
    else{
        printf("Excedió el numero de productos\n");
    }
}



/* 
int obtenerCantidadJugadores(int argc, char *argv[])
{
    int cantidad;
    
    if(argc != 2){
        printf("La cantidad de jugadores debe ser entre 1 y %d\n", MAX_CANT_JUGADORES);
        exit(0);
    }
    
    cantidad = atoi(argv[1]);
    
    if(cantidad < 1 || cantidad > MAX_CANT_JUGADORES){
        printf("La cantidad de jugadores debe ser entre 1 y %d\n", MAX_CANT_JUGADORES);
        exit(0);
    }
    return cantidad;
}
 */

