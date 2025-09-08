CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread

all: clean carga reservas

carga : carga.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o carga carga.c archivos.c semaforos.c clave.c global.c funciones.c

reservas : reservas.c archivos.h semaforos.h clave.h def.h global.h funciones.h
	$(CC) $(FLAGS) -o reservas reservas.c archivos.c semaforos.c clave.c global.c funciones.c

clean: 
	rm -rf *.o carga reservas *.dat
