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
    char buffer[LARGO];
    /*Declaracion de variables*/
    /*Memset*/
    /*obtengo e inicializo el semaforo*/
	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, 1);
    while(1){
        espera_semaforo(id_semaforo);
        /*Menu/Logica productor*/
        inEscribirArchivo(ARCHIVO, buffer);
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);
    }
    return 0;   
}
