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
    Juego *memoria = NULL;
    int id_semaforo;
    int intentos = 0;
    int numerosAleatorios[HASTA - DESDE + 1];
    int i = 0;
    
    /* Inicializo la memoria compartida y obtengo el semaforo */
    memoria = (Juego *)creo_memoria(sizeof(Juego), &id_memoria, CLAVE_BASE);
    id_semaforo = creo_semaforo();
    srand(time(NULL));
    
    /* Genero todos los números aleatorios no repetitivos */
    inDevolverNumeroAleatorioNoRepetitivo(numerosAleatorios, DESDE, HASTA);
     /* Verifico que el semaforo este inicializado */
     if(!inExisteArchivo("semaforoInicializado.dat"))
     {
         printf("Semaforo no inicializado, debe correr el programa pienso primero\n");
         exit(0);
     }
    printf("Ingrese su nombre: ");
    scanf("%s", memoria->nombre_jugador);

   
    id_semaforo = creo_semaforo();
    while (1)
    {
        espera_semaforo(id_semaforo);

        while (1)
        {   
            /*Voy pensando numeros de la secuencia no repetitiva*/
            if(memoria->numero_pensado == 0 && memoria->estado_acierto == 0 && i < (HASTA - DESDE + 1))
            {
                memoria->numero_pensado = numerosAleatorios[i];
                i++;
                intentos++;
                printf("Intento #%d - Pruebo con el número: %d\n", intentos, memoria->numero_pensado);
                break;
            }
            break;
        }
        /* Libero el semaforo para que Pienso pueda ver si acerte */
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);
        /* Una vez que Pienso verifico que acerte, muestro el numero de intentos */
        if(memoria->estado_acierto == 1)
        {
            printf("Acerté tras %d intentos! El número era %d.\n", intentos, memoria->numero_pensado);
            break;
        }
    }
    
    /* Libero la memoria compartida */
    shmdt((char *)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
