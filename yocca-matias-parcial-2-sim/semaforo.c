#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include "semaforo.h"
#include "clave.h"

int semaforo_crear(int claveBase)
{

    key_t clave = clave_crear(claveBase);
    int id_semaforo = semget(clave, 1, 0600 | IPC_CREAT);

    if (id_semaforo == -1)
    {
        printf("Error: no se puede crear el semaforo\n");
        exit(0);
    }
    return id_semaforo;
}

void semaforo_iniciar(int id_semaforo, int valor)
{
    semctl(id_semaforo, 0, SETVAL, valor);
}

void semaforo_levantar(int id_semaforo)
{
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = 1; /*incrementa el semaforo en 1*/
    operacion.sem_flg = 0;
    semop(id_semaforo, &operacion, 1);
}

void semaforo_esperar(int id_semaforo)
{
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = -1; /*decrementa el semaforo en 1*/
    operacion.sem_flg = 0;
    semop(id_semaforo, &operacion, 1);
}
