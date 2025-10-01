#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

key_t creo_clave(char *command, int value) {

	key_t clave;
	clave = ftok(command, value); /* "/bin/ls", 33 */
	
	if(clave == (key_t)-1) {
		printf("Could not generate key_t.\n");
		exit(0);
	}
	
	return clave;	

}

