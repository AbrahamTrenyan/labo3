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
    struct propiedad propiedades[CANT_PROPEDADES]; /*Array de propiedades*/
    int i;
    int id_semaforo;
    int nroPropiedad;
    int cant_propiedades;
    char nombrePropiedad[LARGO];
    char texto[LARGO];

    memset(propiedades, 0, sizeof(propiedades));
    memset(texto, 0, sizeof(texto));
    memset(nombrePropiedad, 0, sizeof(nombrePropiedad));
    cant_propiedades = 0;
    nroPropiedad = 1;
    srand(time(NULL));
    /*obtengo e inicializo el semaforo*/
	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, 1);
    while(cant_propiedades < CANT_PROPEDADES){
        espera_semaforo(id_semaforo);
        printf("Ingrese el nombre de la propiedad (%d/%d): ", cant_propiedades + 1, CANT_PROPEDADES);
		scanf(" %[^\n]",nombrePropiedad);
        
        /* Procesar y escribir la propiedad inmediatamente */
        strcpy(propiedades[cant_propiedades].nombre, nombrePropiedad);
        propiedades[cant_propiedades].metros = inDevolverNumeroAleatorio(MIN_METROS, MAX_METROS);
        propiedades[cant_propiedades].precio = propiedades[cant_propiedades].metros * PRECIO_METRO;
        propiedades[cant_propiedades].id = nroPropiedad + cant_propiedades;
        propiedades[cant_propiedades].estado = 0;
        
        sprintf(texto,"%s\t\t$%d\t%d\t%d\t%d\t%s\t%s\n", 
            propiedades[cant_propiedades].nombre, 
            propiedades[cant_propiedades].precio, 
            propiedades[cant_propiedades].metros, 
            propiedades[cant_propiedades].id, 
            propiedades[cant_propiedades].estado, 
            propiedades[cant_propiedades].reservante, 
            propiedades[cant_propiedades].dni);
        inEscribirArchivo(ARCHIVO, texto);
        
        cant_propiedades++;
        printf("Propiedad %d procesada y guardada.\n", cant_propiedades);
        
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);
    }
    
    printf("\nTodas las %d propiedades han sido guardadas en el archivo.\n", CANT_PROPEDADES);
    return 0;   
}
