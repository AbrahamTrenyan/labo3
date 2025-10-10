#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semaforo.h"
#include "unistd.h"
#include "global.h"
#include "archivos.h"
#include "time.h"
#include "funciones.h"
#include "memoria.h"
#include "clave.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "colas.h"



void atenderCliente(int idColaMensajes, MensajeExtendido *mensaje)
{
    int opcion = 0;
    int id = 0;
    int saldo = 0;

    printf("Ingrese una opcion (Deposito: 1, Consulta saldo: 2, Extraccion: 3):");
    scanf("%d", &opcion);

    printf("\nIngrese su ID de usuario: ");
    scanf("%d", &id);

    switch(opcion)
    {
        case 1: /*  Depositar id + saldo */
            printf("\nIngrese saldo a depositar: ");
            scanf("%d", &saldo);
            enviarMensajeExtendido(idColaMensajes, MENSAJE_A_BANCO, MENSAJE_A_CAJERO, E_DEPOSITO, id, saldo);
            recibirMensajeExtendido(idColaMensajes, MENSAJE_A_CAJERO, mensaje);
            
            if(mensaje->int_evento == E_RESPUESTA_DEPOSITO_OK)
            {
                printf("\nDeposito realizado correctamente");
            } else if(mensaje->int_evento == E_RESPUESTA_DEPOSITO_ERROR)
            {
                printf("\nError al realizar deposito");
            }
            
            break;

        case 2: /*  Consultar saldo, solo id */
            enviarMensajeExtendido(idColaMensajes, MENSAJE_A_BANCO, MENSAJE_A_CAJERO, E_CONSULTA_SALDO, id, saldo);
            recibirMensajeExtendido(idColaMensajes, MENSAJE_A_CAJERO, mensaje);

            if(mensaje->int_evento == E_RESPUESTA_SALDO)
            {
                printf("\nConsulta a saldo ok");
                printf("\nSu saldo actual es: %d", mensaje->saldo);
            } else if(mensaje->int_evento == E_RESPUESTA_SALDO_ERROR)
            {
                printf("\nError al realizar consulta saldo");
            }

            break;

        case 3: /*  Extraccion: id + saldo */
            printf("\nIngrese saldo a extraer: ");
            scanf("%d", &saldo);
            enviarMensajeExtendido(idColaMensajes, MENSAJE_A_BANCO, MENSAJE_A_CAJERO, E_EXTRACCION, id, saldo);

            if(mensaje->int_evento == E_EXTRACCION_OK)
            {
                printf("\nExtraccion de saldo realizada con exito");
            } else if(mensaje->int_evento == E_EXTRACCION_ERROR)
            {
                printf("\nError al extraer saldo");
            }

            break;

    }

    


}




int main(int argc, char *argv[])
{
    int idColaMensajes;
    MensajeExtendido mensajeExtendido;
    int continuar = 1;
    
    
    memset(&mensajeExtendido, 0, sizeof(MensajeExtendido));

    idColaMensajes = creoIdColaMensajes();



    while(continuar)
    {

        atenderCliente(idColaMensajes, &mensajeExtendido);

        printf("\n----------\n");

        printf("\nDesea continuar? (SI: 1, NO: 0): ");
        scanf("%d", &continuar);



    }

    liberarColaMensajes(idColaMensajes);

    return 0;
}

