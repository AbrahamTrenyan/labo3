#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cola.h"
#include "clave.h"
#include "funciones.h"

int main(int argc, char *argv[])
{
    int i, clave, cola_id, ganador;
    int remitente_id, objetivo_id, danio;
    mensaje_t mensaje;
    int vida_luchadores[CANTIDAD_EQUIPOS * CANTIDAD_LUCHADORES_POR_EQUIPO];

    printf("Iniciando arena...\n");

    srand(time(NULL));
    inicializar_vida_base(VIDA_BASE);
    clave = clave_crear(CLAVE_BASE);
    cola_id = cola_crear(clave);

    for (i = 0; i < CANTIDAD_EQUIPOS * CANTIDAD_LUCHADORES_POR_EQUIPO; i++)
    {
        vida_luchadores[i] = VIDA_BASE;
    }

    esperar_inicio(1);

    printf("Arena iniciada\n");

    while (1)
    {
        cola_recibir(cola_id, DEST_ARENA, &mensaje);
        remitente_id = mensaje.remitente - DEST_LUCHADOR;

        switch (mensaje.evento)
        {
        case EVT_ATAQUE:
            obtener_objetivo_danio(mensaje.mensaje, &objetivo_id, &danio);
            procesar_ataque(vida_luchadores, cola_id, remitente_id, objetivo_id, danio);
            ganador = verificar_fin_juego(vida_luchadores);
            if (ganador != SIGUE_EL_JUEGO)
            {
                printf("El juego ha terminado. El equipo %d ha ganado\n", ganador);
                cola_enviar(cola_id, DEST_CONTROLADOR, DEST_ARENA, EVT_FIN, "");
                return 0;
            }
            break;
        default:
            printf("[arena] Mensaje desconocido: %d\n", mensaje.evento);
            break;
        }
    }

    return 0;
}
