CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89
all: clean productor consumidor

productor : productor.c archivos.h
	$(CC) $(FLAGS) -o productor productor.c archivos.c

consumidor : consumidor.c archivos.h
	$(CC) $(FLAGS) -o consumidor consumidor.c archivos.c

clean: 
	rm -rf *.o productor consumidor

