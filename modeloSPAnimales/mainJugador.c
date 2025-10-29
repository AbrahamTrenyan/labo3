#include <pthread.h>
#include <unistd.h>
#include "threads.h"
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

#define DEFAULT 0

typedef enum
{
	MENSAJE_NADIE, /* 0 */
	MENSAJE_TABLERO,
    MENSAJE_CONEJO,
	MENSAJE_GATO,
	MENSAJE_PERRO
} Mensajes;

typedef enum
{
	EVENTO_INICIO, /* 0 */
	EVENTO_NINGUNO, 
	EVENTO_AVANZAR,
	EVENTO_FIN
	

} Eventos;

typedef struct
{
    int idColaMensajes;
    /* Cada uno tiene el suyo */
    int numeroJugador;
    int posicion;

    /* Todos saben: */
    int meta;

    int *juegoTerminado;

} ThreadData;

void avanzarAnimales(ThreadData *threadData)
{

    int numeroAleatorio = 0;
    int idColaMensajes = threadData->idColaMensajes;

    if(threadData->numeroJugador == MENSAJE_CONEJO)
    {
        
        printf("\nSoy el conejo...");
        /* Toda esta accion es atómica, no se interrumpe. El nucleo está solo con esta accion */
        numeroAleatorio = devolverNumeroAleatorio(4, 9);

        threadData->posicion += numeroAleatorio;

        /* Tambien... atómico ! */
        enviarMensajeExtendido(idColaMensajes, MENSAJE_TABLERO, MENSAJE_CONEJO, EVENTO_AVANZAR, threadData->posicion, DEFAULT);
    } else if(threadData->numeroJugador == MENSAJE_GATO)
    {

        printf("\nSoy el gato...");
        /* Toda esta accion es atómica, no se interrumpe. El nucleo está solo con esta accion */
        numeroAleatorio = devolverNumeroAleatorio(1, 10);

        threadData->posicion += numeroAleatorio;

        /* Tambien... atómico ! */
        enviarMensajeExtendido(idColaMensajes, MENSAJE_TABLERO, MENSAJE_GATO, EVENTO_AVANZAR, threadData->posicion, DEFAULT);
    } else if(threadData->numeroJugador == MENSAJE_PERRO)
    {

        printf("\nSoy el perro...");
        /* Toda esta accion es atómica, no se interrumpe. El nucleo está solo con esta accion */
        numeroAleatorio = devolverNumeroAleatorio(3, 8);

        threadData->posicion += numeroAleatorio;

        /* Tambien... atómico ! */
        enviarMensajeExtendido(idColaMensajes, MENSAJE_TABLERO, MENSAJE_PERRO, EVENTO_AVANZAR, threadData->posicion, DEFAULT);

    }

    printf("\nVoy a avanzar %d pasos\n", numeroAleatorio);


}



void *funcionThread(void *parametro)
{
    MensajeExtendido mensaje;
    ThreadData *threadData;
    int *retorno = malloc(sizeof(int));
    int idColaMensajes = 0;

    /* Utilizamos ganeYo para que se envie solo una
       vez en EVENTO_FIN y no arruinar el sincronizmo */
    int ganeYo = 0;

    

    memset(&mensaje, 0, sizeof(MensajeExtendido));

    threadData = (ThreadData *)parametro;

    idColaMensajes = threadData->idColaMensajes;

    while(*(threadData->juegoTerminado) == 0)
    {
        
        pthread_mutex_lock(&mutex);
        /* Todo lo que pasa aca no se interrumpe, es atomico */

        if(*(threadData->juegoTerminado) == 0)
        {
            avanzarAnimales(threadData);
        }
        

        /* Nos fijamos si ganamos... */
        /* Y lo hacemos aca porque vamos a acceder y quizas
           configurar la variable critica/compartida que es
           juegoTerminado.

           Hay que asegurarnos que solo un proceso a la vez acceda y es dentro del mutex   
        */

        if(threadData->posicion >= threadData->meta && *(threadData->juegoTerminado) == 0)
        {
            *(threadData->juegoTerminado) = 1;
            ganeYo = 1;
        }

        pthread_mutex_unlock(&mutex);

        /* El EVENTO_FIN se puede enviar fuera del mutex ya que se manda solo una vez 
           y en los papeles no arruina el sincronismo */
        if(ganeYo == 1)
        {
            printf("\nAnimal %d: LLEGUÉ A LA META! \n", threadData->numeroJugador);
            enviarMensajeExtendido(idColaMensajes, MENSAJE_TABLERO, threadData->numeroJugador, EVENTO_FIN, DEFAULT, DEFAULT);
        }
        
        usleep(300000);


    }

    *retorno = threadData->posicion;

    free(threadData);

    pthread_exit((void *)retorno);
    
}



int main(int argc, char *argv[])
{
    int i;
    int idColaMensajes;
    int idMemoria;
    int *valorDevuelto = NULL;
    int *memoria = NULL;
    pthread_t idHilo[15];

    int pasosMeta = 0;
    int juegoTerminado = 0;
    int posicionConejo = 0;
    int posicionGato = 0;
    int posicionPerro = 0;

    memset(idHilo, 0, sizeof(idHilo));

    idColaMensajes = creoIdColaMensajes();

    esperarFlag();

    srand(time(NULL));


    pthread_mutex_init (&mutex, NULL);
	
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

    printf("\nPresione ENTER para iniciar los hilos...\n");
    getchar();

    memoria = (int*)creo_memoria(sizeof(int) , &idMemoria, 33);

    pasosMeta = *memoria;

    for(i = 0; i < 3; i++)
    {

        ThreadData *threadData = (ThreadData *)calloc(1, sizeof(ThreadData));

        if(threadData == NULL)
		{
			perror("Error en calloc para threadData\n");
			exit(-1);
		}

        /*
        int idColaMensajes;
        int numeroJugador;

        int *meta;

        int *juegoTerminado;

        int *posicionConejo;
        int *posicionGato;
        int *posicionPerro;
        */


        threadData->idColaMensajes = idColaMensajes;
        if(i == 0)
        {
            threadData->numeroJugador = MENSAJE_CONEJO;
        }
        if(i == 1)
        {
            threadData->numeroJugador = MENSAJE_GATO;
        }
        if(i == 2)
        {
            threadData->numeroJugador = MENSAJE_PERRO;
        }
        threadData->meta = pasosMeta;
        threadData->juegoTerminado = &juegoTerminado;
        threadData->posicion = 0;
 
        



        if(pthread_create(&idHilo[i], &atributos, funcionThread, (void *)threadData))
		{
			/*  le pasamos funcionThread, que es "lo que tiene que hacer cada hilo" */
			perror ("No puedo crear thread");
			exit (-1);
		}

    }

    
    for(i = 0; i < 3; i++)
    {

        pthread_join (idHilo[i], (void **)&valorDevuelto); 
        

        if (valorDevuelto != NULL) {
            if(i == 0)
            {
                posicionConejo = *valorDevuelto;
            }

            if(i == 1)
            {
                posicionGato = *valorDevuelto;
            }

            if(i == 2)
            {
                posicionPerro = *valorDevuelto;
            }

            free(valorDevuelto); 
        }
    }

    printf("\nFIN CARRERA");
    printf("\n--- RESULTADOS ---\n");
    printf("\nConejo: %d - Gato: %d - Perro: %d\n", posicionConejo, posicionGato, posicionPerro);



    sleep(3);
    pthread_mutex_destroy(&mutex);
    pthread_attr_destroy(&atributos);

    liberarColaMensajes(idColaMensajes);




    return 0;
}

