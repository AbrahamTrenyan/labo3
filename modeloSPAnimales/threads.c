#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANTIDAD 10

/* pthread_mutex_t mutex; */

/*
void *funcionThread (void *parametro)
{
	int i;
	printf ("Hijo\n");
	for(i=0; i<CANTIDAD; i++)
	{
		pthread_mutex_lock (&mutex);
			printf("Soy el hijo y tengo el mutex\n");
			sleep (1);
		pthread_mutex_unlock (&mutex);
		sleep(1);
	}
	printf("Soy el hijo y espero 10seg\n");
	sleep (10);
	printf("Hijo  : Termino\n");
	pthread_exit ((void *)"Listo");
}

*/



