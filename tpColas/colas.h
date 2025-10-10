#ifndef _colas_h
#define _colas_h


typedef struct
{
    long long_dest;
    int int_rte;
    int int_evento;
    char char_mensaje[100];
} Mensaje;

typedef struct
{
    long long_dest;
    int int_rte;
    int int_evento;
    int id;
    int saldo;
} MensajeExtendido;

int creoIdColaMensajes(void);

int enviarMensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg);

int recibirMensaje(int id_cola_mensajes, long rLongDest, Mensaje* rMsg);

int enviarMensajeExtendido(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, int id, int saldo);

int recibirMensajeExtendido(int id_cola_mensajes, long rLongDest, MensajeExtendido* rMsg);

void liberarColaMensajes(int id_cola_mensajes);



#endif
