#include "memoria.h"
#include "clave.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "colas.h"
#include "global.h"
#include "sys/msg.h"




int creoIdColaMensajes(void)
{
    int idColaMensajes = msgget(creoClave(), 0777 | IPC_CREAT);

    if(idColaMensajes == -1)
    {
        printf("Error al obtener identificador para cola de mensajes\n");
        exit(-1);
    }

    return idColaMensajes;

}

int enviarMensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg)
{
    Mensaje msg;
    
    msg.long_dest = rLongDest;
    msg.int_rte = rIntRte;
    msg.int_evento = rIntEvento;

    strcpy(msg.char_mensaje, rpCharMsg);

    return msgsnd(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje), IPC_NOWAIT);


}



int recibirMensaje(int id_cola_mensajes, long rLongDest, Mensaje* rMsg)
{
    Mensaje msg;
    int res;

    res = msgrcv (id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje), rLongDest, 0);

    rMsg->long_dest = msg.long_dest;
    rMsg->int_rte = msg.int_rte;
    rMsg->int_evento = msg.int_evento;
    strcpy(rMsg->char_mensaje, msg.char_mensaje);
    return res;


}

int enviarMensajeExtendido(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, int n1, int n2)
{
    MensajeExtendido msg;
    
    msg.long_dest = rLongDest;
    msg.int_rte = rIntRte;
    msg.int_evento = rIntEvento;

    msg.n1 = n1;
    msg.n2 = n2;

    return msgsnd(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.n1) + sizeof(msg.n2), IPC_NOWAIT);


}

int recibirMensajeExtendido(int id_cola_mensajes, long rLongDest, MensajeExtendido* rMsg)
{
    MensajeExtendido msg;
    int res;

    res = msgrcv (id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.n1) + sizeof(msg.n2), rLongDest, 0);

    rMsg->long_dest = msg.long_dest;
    rMsg->int_rte = msg.int_rte;
    rMsg->int_evento = msg.int_evento;
    rMsg->n1 = msg.n1;
    rMsg->n2 = msg.n2;
    return res;


}


void liberarColaMensajes(int id_cola_mensajes)
{
    if (msgctl(id_cola_mensajes, IPC_RMID, NULL) == -1) 
    {
        printf("Error al eliminar la cola de mensajes");
    } else {
        printf("Cola de mensajes eliminada correctamente.\n");
    }
}

void borrarMensajesViejos(int idColaMensajes)
{
    MensajeExtendido mensaje;
    int res = 0;

    printf("\nBorrando colas de mensajes viejas\n");

    while(res != -1)
    {
        res = msgrcv(idColaMensajes, &mensaje, sizeof(MensajeExtendido) - sizeof(long), 0, IPC_NOWAIT);
    }
}

