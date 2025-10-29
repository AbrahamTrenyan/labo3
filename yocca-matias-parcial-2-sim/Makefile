CC = gcc
CFLAGS = -Wall -pedantic-errors -std=gnu89 -O3 -pthread
HEADER = -I./
MISC = funciones.c global.c archivos.c semaforo.c clave.c memoria.c thread.c cola.c

all: arena equipo

arena: 01-arena.c $(MISC)
	$(CC) -o arena $(CFLAGS) $(HEADER) $(MISC) 01-arena.c

equipo: 02-equipo.c $(MISC)
	$(CC) -o equipo $(CFLAGS) $(HEADER) $(MISC) 02-equipo.c

clean:
	rm -f *.o arena equipo start.dat