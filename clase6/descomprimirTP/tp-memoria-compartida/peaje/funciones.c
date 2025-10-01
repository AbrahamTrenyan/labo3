#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
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

void registrar_liberacion(char *buffer, int *cantidad_de_liberaciones)
{
    /*Leo el archivo y obtengo la cantidad actual de liberaciones*/
    if(inAbrirArchivo("liberacion.dat", "r"))
    {
        if(inLeerArchivo(buffer))
        {
            *cantidad_de_liberaciones = atoi(buffer);
        }
        voCerrarArchivo();
    }
    (*cantidad_de_liberaciones)++;
    sprintf(buffer, "%d\n", *cantidad_de_liberaciones);
    /*Sobrescribo el archivo con el nuevo valor*/
    inEscribirArchivo("liberacion.dat", buffer, "w");
}
void obtener_via_con_menos_vehiculos(int *vehiculos_en_cola, int cantidad_de_vias, int *via_seleccionada, int *minimo, int *i){
    *via_seleccionada = 0;
    *minimo = vehiculos_en_cola[0];
    
    for(*i = 1; *i < cantidad_de_vias; (*i)++){
        if(vehiculos_en_cola[*i] < *minimo){
            *minimo = vehiculos_en_cola[*i];
            *via_seleccionada = *i;
        }
    }
}

void obtener_cantidad_de_vias(int argc, char *argv[], int *cantidad_de_vias){
    if(argc != 2){
        printf("Debe ingresar la cantidad de vias como parametro\n");
        exit(0);
    }
    if(atoi(argv[1]) < 1 || atoi(argv[1]) > MAX_VIAS){
        printf("La cantidad de vias debe ser entre 1 y %d\n", MAX_VIAS);
        exit(0);
    }
    *cantidad_de_vias = atoi(argv[1]);
    printf("Cantidad de vias: %d\n", *cantidad_de_vias);
}

