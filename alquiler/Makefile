#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean carga reservante		

carga : carga.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o carga carga.c archivos.c semaforos.c clave.c global.c funciones.c

reservante : reservante.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o reservante reservante.c archivos.c semaforos.c clave.c global.c funciones.c

clean: 
	rm -rf *.o carga reservante *.dat