#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "def.h"
#include "semaforos.h"

int main(int argc, char *argv[])
{
    int id_semaforo;
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);

    if (id_semaforo != -1)

    {
        printf("Hola %d\n", id_semaforo);

        espera_semaforo(id_semaforo);

        levanta_semaforo(id_semaforo);

        usleep(500 * 1000);
    }
    return 0;
}
