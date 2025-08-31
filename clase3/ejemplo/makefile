CC = gcc
FLAGS = -Wall -pedantic-errors -O3 -std=gnu89 -pthread
all = clean main

main : main.c def.h archivos.h global.h archivos.h
	$(CC) $(FLAGS) -o main main.c  archivos.c global.c 

clean: 
	rm -rf *.o main

