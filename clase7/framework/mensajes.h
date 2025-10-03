#ifndef _MENSAJE
#define _MENSAJE

int creo_id_cola_mensajes(int clave);
int enviar_mensaje(int id_Cola_Mensajes);
int recibir_mensaje(int id_Cola_Mensajes);
int borrar_cola_de_mensajes(int Id_Cola_Mensajes);
int borrar_mensajes(int id_cola_mensajes);

/* Estructura para los mensajes que se quieren enviar y/o recibir. Deben llevar
 obligatoriamente como primer campo un long para indicar un identificador
 del mensaje. 
 Los siguientes campos son la información que se quiera transmitir en el  
 mensaje. Cuando más adelante, en el código, hagamos un cast a 
 (struct msgbuf *), todos los campos de datos los verá el sistema como
 un único (char *) */
*/

typedef struct mensaje
{
	long	long_dest; 						/*Destinatario*/
	int 	int_rte;						/*Remitente*/
	int 	int_evento;						/*Numero de evento*/
	char 	char_mensaje[LARGO_TMENSAJE];	/*mensaje*/
}msg;
;

/* estructura para envio mensajes*/
#endif

