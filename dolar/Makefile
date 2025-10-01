CC=gcc-4.1

CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors
HEADERS = -I./

all: clean cajero banco

cajero: cajero.c clave.c semaforo.c archivos.c
	$(CC) -o cajero cajero.c clave.c semaforo.c archivos.c $(CFLAGS) $(HEADERS)

banco: banco.c clave.c semaforo.c archivos.c
	$(CC) -o banco banco.c clave.c semaforo.c archivos.c $(CFLAGS) $(HEADERS)

clean:
	rm -rf *.o cajero banco
