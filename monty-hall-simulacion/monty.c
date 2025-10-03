#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int intentos = 10000000;   /* número de simulaciones */
    int i;
    int puertaPremio, eleccionInicial, puertaMostrada, cambioPuerta;
    int ganarCambiando = 0;
    int ganarQuedandose = 0;

    srand(time(NULL));

    for (i = 0; i < intentos; i++) {
        puertaPremio = rand() % 3;     /* puerta con el premio */
        eleccionInicial = rand() % 3;      /* elección inicial */

        do {
            puertaMostrada = rand() % 3;
        } while (puertaMostrada == eleccionInicial || puertaMostrada == puertaPremio);
        /* puerta si cambiás: la que no elegiste ni mostró el presentador */
        for (cambioPuerta = 0; cambioPuerta < 3; cambioPuerta++) {
            if (cambioPuerta != eleccionInicial && cambioPuerta != puertaMostrada) break;
        }

        if (cambioPuerta == puertaPremio) {
            ganarCambiando++;
        }
        if (eleccionInicial == puertaPremio) {
            ganarQuedandose++;
        }
    }

    printf("Total de simulaciones: %d\n", intentos);
    printf("Ganando CAMBIANDO: %d (%.2f%%)\n", ganarCambiando, (ganarCambiando * 100.0) / intentos);
    printf("Ganando QUEDÁNDOSE: %d (%.2f%%)\n", ganarQuedandose, (ganarQuedandose * 100.0) / intentos);

    return 0;
}
