#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "clave.h"
#include "def.h"
#include "mensajes.h"
#include "archivos.h"

void mostrar_menu(void)
{
	printf("Cajero Automatico\n");
	printf("1. Consultar saldo\n");
	printf("2. Realizar deposito\n");
	printf("3. Realizar extraccion\n");
	printf("4. Salir\n");
}

void consultar_saldo(int id_cola_mensajes, int id_cajero)
{
	int cod_cliente, saldo;
	char mensaje[LARGO_MENSAJE];
	char error[LARGO_MENSAJE];
	Mensaje mensaje_recibido;
	
	printf("\nConsultar saldo\n");
	printf("Ingrese codigo de cliente (0-99): ");
	scanf("%d", &cod_cliente);
	
	sprintf(mensaje, "%d", cod_cliente);
	
	printf("Enviando consulta al banco\n");
	enviar_mensaje(id_cola_mensajes, MENSAJE_A_BANCO, id_cajero, EVT_CONSULTA_SALDO, mensaje);
	
	printf("Esperando respuesta del banco\n");
	recibir_mensaje(id_cola_mensajes, id_cajero, &mensaje_recibido);
	
	if (mensaje_recibido.int_evento == EVT_RTA_SALDO) {
		sscanf(mensaje_recibido.char_mensaje, "%d|%d", &cod_cliente, &saldo);
		printf("\nSaldo del cliente %d: $%d\n\n", cod_cliente, saldo);
	} else if (mensaje_recibido.int_evento == EVT_RTA_SALDO_NOK) {
		sscanf(mensaje_recibido.char_mensaje, "%d|%[^\n]", &cod_cliente, error);
		printf("\nError: %s\n\n", error);
	}
}

void realizar_deposito(int id_cola_mensajes, int id_cajero)
{
	int cod_cliente, importe, saldo;
	char mensaje[LARGO_MENSAJE];
	char error[LARGO_MENSAJE];
	Mensaje mensaje_recibido;
	
	printf("\nRealizar deposito\n");
	printf("Ingrese codigo de cliente (0-99): ");
	scanf("%d", &cod_cliente);
	printf("Ingrese importe a depositar: $");
	scanf("%d", &importe);
	
	sprintf(mensaje, "%d|%d", cod_cliente, importe);
	
	printf("Enviando deposito al banco\n");
	enviar_mensaje(id_cola_mensajes, MENSAJE_A_BANCO, id_cajero, EVT_DEPOSITO, mensaje);
	
	printf("Esperando respuesta del banco\n");
	recibir_mensaje(id_cola_mensajes, id_cajero, &mensaje_recibido);
	
	if (mensaje_recibido.int_evento == EVT_RTA_DEPOSITO_OK) {
		sscanf(mensaje_recibido.char_mensaje, "%d|%d", &cod_cliente, &saldo);
		printf("\nDeposito realizado correctamente\n");
		printf("Cliente: %d\n", cod_cliente);
		printf("Nuevo saldo: $%d\n\n", saldo);
	} else if (mensaje_recibido.int_evento == EVT_RTA_DEPOSITO_NOK) {
		sscanf(mensaje_recibido.char_mensaje, "%d|%[^\n]", &cod_cliente, error);
		printf("\nError: %s\n\n", error);
	}
}

void realizar_extraccion(int id_cola_mensajes, int id_cajero)
{
	int cod_cliente, importe, saldo;
	char mensaje[LARGO_MENSAJE];
	char error[LARGO_MENSAJE];
	Mensaje mensaje_recibido;
	
	printf("\nRealizar extraccion\n");
	printf("Ingrese codigo de cliente (0-99): ");
	scanf("%d", &cod_cliente);
	printf("Ingrese importe a extraer: $");
	scanf("%d", &importe);
	
	sprintf(mensaje, "%d|%d", cod_cliente, importe);
	
	printf("Enviando extraccion al banco\n");
	enviar_mensaje(id_cola_mensajes, MENSAJE_A_BANCO, id_cajero, EVT_EXTRACCION, mensaje);
	
	printf("Esperando respuesta del banco\n");
	recibir_mensaje(id_cola_mensajes, id_cajero, &mensaje_recibido);
	
	if (mensaje_recibido.int_evento == EVT_RTA_EXTRACCION_OK) {
		sscanf(mensaje_recibido.char_mensaje, "%d|%d", &cod_cliente, &saldo);
		printf("\nExtraccion realizada correctamente\n");
		printf("Cliente: %d\n", cod_cliente);
		printf("Nuevo saldo: $%d\n\n", saldo);
	} else if (mensaje_recibido.int_evento == EVT_RTA_EXTRACCION_NOK) {
		sscanf(mensaje_recibido.char_mensaje, "%d|%[^\n]", &cod_cliente, error);
		printf("\nError: %s\n\n", error);
	}
}

void obtener_numero_cajero(int argc, char *argv[], int *id_cajero)
{
    if (argc != 2) {
        printf("Debe indicar el numero de cajero\n");
        exit(1);
    }
    *id_cajero = atoi(argv[1]);

    if (*id_cajero == MENSAJE_A_BANCO) {
        printf("Error: El ID del cajero no puede ser %d (reservado para el banco)\n", MENSAJE_A_BANCO);
        printf("Use un numero diferente.\n");
        exit(1);
    }
    
        
}

int main(int argc, char *argv[])
{
	int id_cola_mensajes;
	int opcion;
    int id_cajero;
    /*Validacion para que al ejecutar primero el cajero, salte un error*/
    if (!inExisteArchivo("bancoInicializado.dat")) {
        printf("No se inicializo el banco. Debe correr el programa banco primero\n");  
        voCerrarArchivo();
        exit(0);
    }

    obtener_numero_cajero(argc, argv, &id_cajero);
	/*Obtengo id de cola de mensajes*/
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    printf("Cajero: %d\n", id_cajero);
    
	while (1) {
        mostrar_menu();
        
		printf("Ingrese opcion: ");
		scanf("%d", &opcion);
		
		switch (opcion) {
			case 1:
				consultar_saldo(id_cola_mensajes, id_cajero);
				break;
			case 2:
				realizar_deposito(id_cola_mensajes, id_cajero);
				break;
			case 3:
				realizar_extraccion(id_cola_mensajes, id_cajero);
				break;
			case 4:
				printf("Saliendo del cajero.\n");
				return 0;
			default:
				printf("Opcion invalida.\n");
		}
		
		usleep(500 * MS);
	}
	
	return 0;
}
