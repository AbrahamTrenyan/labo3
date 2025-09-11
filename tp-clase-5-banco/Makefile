CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean cajero tesorero

cajero : cajero.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o cajero cajero.c archivos.c semaforos.c clave.c global.c funciones.c

tesorero : tesorero.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o tesorero tesorero.c archivos.c semaforos.c clave.c global.c funciones.c

clean: 
	rm -rf *.o cajero tesorero *.dat *.999.dat
