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
    /*Declaracion de variables*/
    char ciudadOrigen[LARGO];
    char linea[LARGO];
    char nombreArchivo[LARGO];
    int nroAvion;
    /*Memset*/
    memset(ciudadOrigen, 0, sizeof(ciudadOrigen));
    memset(linea, 0, sizeof(linea));
    memset(nombreArchivo, 0, sizeof(nombreArchivo));
    /*obtengo el id de semaforo*/
	id_semaforo = creo_semaforo();
    /*Verifico si paso el argumento y obtengo numero de avion*/
    obtener_numero_avion(argc, argv, &nroAvion);
    /*Genero el nombre del archivo especifico para este avion*/
    sprintf(nombreArchivo, "avion%d.dat", nroAvion);
    while(1){
        espera_semaforo(id_semaforo);
        printf("Tengo el token\n");
        /*Menu/Logica avion*/
        memset(ciudadOrigen, 0, sizeof(ciudadOrigen));
        memset(linea, 0, sizeof(linea));
        printf("Ingrese la ciudad de origen del avion: ");
        fgets(ciudadOrigen, LARGO, stdin);
        /*Elimino el salto de linea si existe*/
        if (ciudadOrigen[strlen(ciudadOrigen) - 1] == '\n') {
            ciudadOrigen[strlen(ciudadOrigen) - 1] = '\0';
        }
        sprintf(linea, "%d %s\n", nroAvion, ciudadOrigen);
        /*Sobreescribo el archivo*/
        inEscribirArchivo(nombreArchivo, linea, "w");
        /*FIN Menu/Logica avion*/
        levanta_semaforo(id_semaforo);
        usleep(2000 * MS);
    }
    return 0;   
}
