#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include "cola.h"
#include "clave.h"

int cola_crear(int clave)
{
  int cola_id = msgget(clave_crear(clave), 0600 | IPC_CREAT);
  if (cola_id == -1)
  {
    printf("Error al obtener identificador para cola mensajes\n");
    exit(-1);
  }
  return cola_id;
}

int cola_enviar(int cola_id, long destinatario, int remitente,
                int evento, char *mensaje)
{
  mensaje_t msg;
  int size;
  msg.destinatario = destinatario;

  msg.remitente = remitente;
  msg.evento = evento;

  if (mensaje != NULL)
  {
    strcpy(msg.mensaje, mensaje);
  }
  else
  {
    msg.mensaje[0] = '\0';
  }

  size =
      sizeof(msg.remitente) + sizeof(msg.evento) + sizeof(msg.mensaje);

  return msgsnd(cola_id, (struct msgbuf *)&msg, size, IPC_NOWAIT);
}

int cola_recibir(int cola_id, long destinatario, mensaje_t *recv_msg)
{
  mensaje_t msg;
  int res;
  int size;

  size =
      sizeof(msg.remitente) + sizeof(msg.evento) + sizeof(msg.mensaje);

  res = msgrcv(cola_id, (struct msgbuf *)&msg, size, destinatario, 0);

  recv_msg->destinatario = msg.destinatario;
  recv_msg->remitente = msg.remitente;
  recv_msg->evento = msg.evento;

  strcpy(recv_msg->mensaje, msg.mensaje);

  return res;
}

int cola_borrar(int cola_id)
{
  msgctl(cola_id, IPC_RMID, (struct msqid_ds *)NULL);
  return 0;
}

int cola_borrar_mensajes(int cola_id)
{
  mensaje_t msg;
  int res;
  do
  {
    res = msgrcv(cola_id, (struct msgbuf *)&msg,
                 sizeof(msg.remitente) + sizeof(msg.evento) +
                     sizeof(msg.mensaje),
                 0, IPC_NOWAIT);

  } while (res > 0);
  return res;
}
