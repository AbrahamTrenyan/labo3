#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include "unistd.h"
#include "semaforo.h"
#include "clave.h"


/* funcion que crea semaforo */
int creoSemaforo(void)
{
    key_t clave = creoClave();
    int id_semaforo = semget(clave, 1, 0600 | IPC_CREAT);

    /* Primer parametro es la clave, el... */
    if(id_semaforo == -1)
    {
        printf("Error: no puedo crear semaforo\n");
        exit(0);
    }
    return id_semaforo;

}

/* Inicia el semaforo */
void inicioSemaforo(int id_semaforo, int valor)
{
    semctl(id_semaforo, 0, SETVAL, valor);
}

/* Levanta el semaforo */
void levantaSemaforo(int id_semaforo)
{
    struct sembuf operacion;
    printf("Levanta SEMAFORO \n");
    operacion.sem_num = 0;
    operacion.sem_op = 1; /*  Incrementa el semaforo en 1 */
    operacion.sem_flg = 0;
    semop(id_semaforo, &operacion, 1);
}

/* Espera semaforo */
void esperaSemaforo(int id_semaforo)
{
    struct sembuf operacion;
    printf("Espera SEMAFORO \n");
    operacion.sem_num = 0;
    operacion.sem_op = -1; /*  Decrementa el semaforo en 1 */
    operacion.sem_flg = 0;
    semop(id_semaforo, &operacion, 1);
}






