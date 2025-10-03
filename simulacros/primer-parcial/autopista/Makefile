#CC = gcc-4.1
CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean cci pmv

cci: cci.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o cci cci.c archivos.c semaforos.c clave.c global.c funciones.c

pmv: pmv.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o pmv pmv.c archivos.c semaforos.c clave.c global.c funciones.c

clean: 
	rm -rf *.o cci pmv *.dat