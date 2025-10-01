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
    int id_semaforo;
    char nombreArchivo[LARGO];
    char texto[LARGO];
    int equipo;
    int gol;
    int numero_aleatorio;
    int tiro;
    obtener_equipo(argc, argv, &equipo);
    memset(texto, 0, sizeof(texto));
    memset(nombreArchivo, 0, sizeof(nombreArchivo));
    /*Genero semilla de numeros aleatorios*/
    srand(time(NULL));
    /*obtengo el semaforo*/
	id_semaforo = creo_semaforo();
    sprintf(nombreArchivo, "equipo%d.dat", equipo);
    printf("Equipo %d: Disponible, esperando goles\n", equipo);
    while(1){
        espera_semaforo(id_semaforo);
        if(inExisteArchivo("partidoTerminado.dat")){
            voCerrarArchivo();
            exit(0);
        }
        else{
        printf("Ingresa un numero del 1 al 3: ");
            scanf("%d", &tiro);
            numero_aleatorio = inDevolverNumeroAleatorio(1, 3);
            if(numero_aleatorio == tiro){
                gol = 1;
                printf("Gol\n");
            }else{
                gol = 0;
                printf("Fuera\n");
            }
        sprintf(texto, "%d\n", gol);
        inEscribirArchivo(nombreArchivo, texto);
        }
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);
    }
    return 0;   
}
