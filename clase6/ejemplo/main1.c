#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "memoria.h"
#include "archivos.h"
#include "semaforos.h"
#include "clave.h"
#include "def.h"
#include "funciones.h"

int main(int argc, char *argv[])
{
    /*Declaracion de variables*/
    int id_memoria;
    dato *memoria = NULL;
    int i, aleatorio;
    int id_semaforo;

    memoria = (dato *)creo_memoria(sizeof(dato) * CANTIDAD, &id_memoria, CLAVE_BASE);
    memset(memoria, 0, sizeof(dato) * CANTIDAD);
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);
    srand(time(NULL));

    while (1)
    {
        espera_semaforo(id_semaforo);
        /*Menu/Logica productor*/
        printf("Escribimos en la memoria\n");
        for (i = 0; i < CANTIDAD; i++)
        {
            aleatorio = inDevolverNumeroAleatorio(DESDE, HASTA);
            memoria[i].numero = aleatorio;
            memoria[i].letra = 0x41 + aleatorio;

            printf("Escrito %d %c\n", memoria[i].numero, memoria[i].letra);
        }
        printf("Dejamos de escribir en la memoria\n");
        levanta_semaforo(id_semaforo);
        usleep(10000 * MS);
    }
    return 0;
}
