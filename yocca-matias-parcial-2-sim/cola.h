#ifndef _COLA_H
#define _COLA_H

typedef struct
{
  long destinatario;
  int remitente;
  int evento;
  char mensaje[100];
} mensaje_t;

int cola_crear(int clave);
int cola_enviar(int cola_id, long destinatario, int remitente,
                int evento, char *mensaje);
int cola_recibir(int cola_id, long destinatario, mensaje_t *recv_msg);
int cola_borrar(int cola_id);
int cola_borrar_mensajes(int cola_id);

#endif
