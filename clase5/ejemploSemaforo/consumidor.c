#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "def.h"
#include "semaforos.h"

int main(int argc, char *argv[])
{
    int id_semaforo;

    id_semaforo = creo_semaforo();
    if (id_semaforo != -1)
    {
        espera_semaforo(id_semaforo);

        printf("chau %d\n", id_semaforo);

        levanta_semaforo(id_semaforo);
    }
    return 0;
}
