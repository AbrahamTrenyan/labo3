#include <stdlib.h>
#include <stdio.h>
#include "clave.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include "def.h"
#include "memoria.h"

void* creo_memoria(int size, int* r_id_memoria) {
	void* ptr_memoria;
	int id_memoria;
	id_memoria = shmget(creo_clave(COMANDO, VALOR_CLAVE), size, 0777 | IPC_CREAT);

	if(id_memoria == -1) {
		printf("\nError: Cannot generate ID for shared memory");
		exit(0);
	}

	ptr_memoria = (void *)shmat(id_memoria, (char *)0, 0);

	if(ptr_memoria == NULL) {
		printf("\nError: Cannot get pointer to shared memory");
		exit(0);

	}

	*r_id_memoria = id_memoria;
	return ptr_memoria;

}

