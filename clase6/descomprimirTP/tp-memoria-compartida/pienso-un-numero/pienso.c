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
    int local_pienso_un_numero;
    int id_semaforo;

    srand(time(NULL));
    printf("Pienso un numero, adivinalo\n");
    local_pienso_un_numero = inDevolverNumeroAleatorio(DESDE, HASTA);

    /* Inicializo la memoria compartida */
    memoria = (Juego *)creo_memoria(sizeof(Juego), &id_memoria, CLAVE_BASE);
    memset(memoria, 0, sizeof(Juego));
    /* Creo e inicializo el semaforo */
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);
    /* Creo el archivo para marcar que el semaforo esta inicializado */
    inEscribirArchivo("semaforoInicializado.dat", "1\n");   
    voCerrarArchivo();
    while (1)
    {
        espera_semaforo(id_semaforo);
        
        /*Si el jugador penso un numero ...*/
        if(memoria->numero_pensado != 0 && memoria->estado_acierto == 0)
        {
            if(memoria->numero_pensado == local_pienso_un_numero)
            {
                /* Si acerto muestro el nombre del ganador */
                memoria->estado_acierto = 1;
                printf("Jugador ganador: %s\n", memoria->nombre_jugador);
            }
            else
            {
                /* Si no acerto, reinicio el numero pensado*/
                memoria->numero_pensado = 0;
                memoria->estado_acierto = 0;
                printf("Numero incorrecto. Intenta de nuevo.\n");
            }
        }
        
        /* Libero el semaforo para que el jugador pueda seguir intentando o ver que gano */
        levanta_semaforo(id_semaforo);
        usleep(100 * MS);

        /* Si acerto, salgo del loop. Puedo leer la memoria sin el semaforo porque 
        el jugador ya no esta escribiendo */
        if(memoria->estado_acierto == 1)
            break;
            
    }
    
    /* Libero la memoria compartida*/
    shmdt((char *)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    
    return 0;
}
