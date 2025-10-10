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

int revisarId(int id)
{
    char nombreArchivo[20];
    memset(nombreArchivo, 0, sizeof(nombreArchivo));

    sprintf(nombreArchivo, "usuario%d.dat", id);

    if(!abrirArchivo(nombreArchivo, "r"))
    {
        return 1;
    } 

    cerrarArchivo();

    return 0;
}

void realizarDeposito(int id, int saldoADepositar)
{
    char usuario[20];
    char szBuffer[15];
    int saldoActual = 0;
    int saldoTotal = 0;

    memset(usuario, 0, sizeof(usuario));
    memset(szBuffer, 0, sizeof(szBuffer));

    sprintf(usuario, "usuario%d.dat", id);

    if(!abrirArchivo(usuario, "r"))
    {
        printf("\nError al abrir archivo");
    }

    while(leerArchivo(szBuffer, sizeof(szBuffer)) == TRUE)
    {
        sscanf(szBuffer, "%d", &saldoActual);
    }

    cerrarArchivo();

    memset(szBuffer, 0, sizeof(szBuffer));

    saldoTotal = saldoActual + saldoADepositar;



    if(!abrirArchivo(usuario, "w"))
    {
        printf("\nError al abrir archivo");
    }

    sprintf(szBuffer, "%d", saldoTotal);

    if(!escribirArchivo(szBuffer))
    {
        printf("\nError al escribir archivo");
    }

    cerrarArchivo();


}

int extraerSaldo(int id, int saldoAExtraer)
{
    char usuario[20];
    char szBuffer[15];
    int saldoActual = 0;
    int saldoTotal = 0;

    memset(usuario, 0, sizeof(usuario));
    memset(szBuffer, 0, sizeof(szBuffer));

    sprintf(usuario, "usuario%d.dat", id);

    if(!abrirArchivo(usuario, "r"))
    {
        printf("\nError al abrir archivo");
    }

    while(leerArchivo(szBuffer, sizeof(szBuffer)) == TRUE)
    {
        sscanf(szBuffer, "%d", &saldoActual);
    }

    cerrarArchivo();

    memset(szBuffer, 0, sizeof(szBuffer));

    saldoTotal = saldoActual - saldoAExtraer;

    if(saldoAExtraer > saldoActual)
    {
        return 1;
    }



    if(!abrirArchivo(usuario, "w"))
    {
        printf("\nError al abrir archivo");
    }

    sprintf(szBuffer, "%d", saldoTotal);

    if(!escribirArchivo(szBuffer))
    {
        printf("\nError al escribir archivo");
    }

    cerrarArchivo();

    return 0;


}



int consultarSaldo(int id)
{
    char usuario[20];
    char szBuffer[15];
    int saldo = 0;

    memset(usuario, 0, sizeof(usuario));
    memset(szBuffer, 0, sizeof(szBuffer));

    sprintf(usuario, "usuario%d.dat", id);

    if(!abrirArchivo(usuario, "r"))
    {
        printf("\nError al abrir archivo");
    }

    /*
    
    while(leerArchivo(szBuffer1, sizeof(szBuffer1)) == TRUE)
    {
        sscanf(szBuffer1, "%d %d %d %d", &numeroIngresado1, &golesAFavor1, &maximoGoles, &numeroAleatorio1);

    }
    
    */

    while(leerArchivo(szBuffer, sizeof(szBuffer)) == TRUE)
    {
        sscanf(szBuffer, "%d", &saldo);
    }

    cerrarArchivo();

    return saldo;

}



void atenderCajero(int idColaMensajes, MensajeExtendido *mensajeExtendido)
{
    int revisado = 0;
    int id = 0;
    int saldo = 0;
    int mati = 0;
    recibirMensajeExtendido(idColaMensajes, MENSAJE_A_BANCO, mensajeExtendido);
    id = mensajeExtendido->id;

    switch (mensajeExtendido->int_evento)
    {
        case E_DEPOSITO:
            revisado = revisarId(mensajeExtendido->id);
            if(revisado == 1)
            {
                enviarMensajeExtendido(idColaMensajes, MENSAJE_A_CAJERO, MENSAJE_A_BANCO, E_RESPUESTA_DEPOSITO_ERROR, id, saldo);
            } else if(revisado == 0)
            {
                realizarDeposito(mensajeExtendido->id, mensajeExtendido->saldo);
                enviarMensajeExtendido(idColaMensajes, MENSAJE_A_CAJERO, MENSAJE_A_BANCO, E_RESPUESTA_DEPOSITO_OK, id, mensajeExtendido->saldo);
            }

            break;

        case E_CONSULTA_SALDO:
            revisado = revisarId(mensajeExtendido->id);
            if(revisado == 1)
            {
                enviarMensajeExtendido(idColaMensajes, MENSAJE_A_CAJERO, MENSAJE_A_BANCO, E_RESPUESTA_SALDO_ERROR, id, saldo);
            } else if(revisado == 0)
            {
                saldo = consultarSaldo(id);
                enviarMensajeExtendido(idColaMensajes, MENSAJE_A_CAJERO, MENSAJE_A_BANCO, E_RESPUESTA_SALDO, id, saldo);
            }

            break;

        case E_EXTRACCION:
            revisado = revisarId(mensajeExtendido->id);

            if(revisado == 1)
            {
                enviarMensajeExtendido(idColaMensajes, MENSAJE_A_CAJERO, MENSAJE_A_BANCO, E_EXTRACCION_ERROR, id, saldo);
            } else
            {
                mati = extraerSaldo(mensajeExtendido->id, mensajeExtendido->saldo);
                if(mati == 1)
                {
                    enviarMensajeExtendido(idColaMensajes, MENSAJE_A_CAJERO, MENSAJE_A_BANCO, E_EXTRACCION_ERROR, id, saldo);
                } else
                {
                    enviarMensajeExtendido(idColaMensajes, MENSAJE_A_CAJERO, MENSAJE_A_BANCO, E_EXTRACCION_OK, id, saldo);
                }
            }

            break;

    }
}



int main(int argc, char *argv[])
{

    int idColaMensajes;
    MensajeExtendido mensajeExtendido;

    memset(&mensajeExtendido, 0, sizeof(MensajeExtendido));

    idColaMensajes = creoIdColaMensajes();


    while(1)
    {
        atenderCajero(idColaMensajes, &mensajeExtendido);
    }
    




    return 0;
}

