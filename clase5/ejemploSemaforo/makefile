CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread
all: clean productor consumidor

productor : productor.c semaforos.h clave.h
	$(CC) $(FLAGS) -o productor productor.c semaforos.c clave.c

consumidor : consumidor.c semaforos.h clave.h
	$(CC) $(FLAGS) -o consumidor consumidor.c semaforos.c clave.c

clean: 
	rm -rf *.o productor consumidor

