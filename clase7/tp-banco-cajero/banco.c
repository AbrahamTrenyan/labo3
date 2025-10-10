#include "clave.h"
#include "def.h"
#include "mensajes.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>
#include "archivos.h"

void procesar_mensajes(int id_cola_mensajes, Mensaje mensaje_recibido, int saldos[]) {
    int cod_cliente, importe;
    char respuesta[LARGO_MENSAJE];

    if (mensaje_recibido.int_evento == EVT_CONSULTA_SALDO) {
        /*Parseo el codigo de cliente*/
        sscanf(mensaje_recibido.char_mensaje, "%d", &cod_cliente); 
        printf("\nRecibi consulta de saldo. Cliente: %d | Remitente: %d\n", cod_cliente, mensaje_recibido.int_rte);
        if (cod_cliente < 0 || cod_cliente >= 100) {
            printf("El cliente no existe\n");
            sprintf(respuesta, "%d|El cliente no existe", cod_cliente);
            enviar_mensaje(id_cola_mensajes, mensaje_recibido.int_rte, MENSAJE_A_BANCO, EVT_RTA_SALDO_NOK, respuesta);
        } else {
            /*Respondo con el saldo del cliente*/
            printf("  Saldo actual: $%d\n", saldos[cod_cliente]);
            sprintf(respuesta, "%d|%d", cod_cliente, saldos[cod_cliente]);
            enviar_mensaje(id_cola_mensajes, mensaje_recibido.int_rte, MENSAJE_A_BANCO, EVT_RTA_SALDO, respuesta);
        }
    }
    else if (mensaje_recibido.int_evento == EVT_DEPOSITO) {
        /*Divido el mensaje en codigo de cliente e importe*/
        sscanf(mensaje_recibido.char_mensaje, "%d|%d", &cod_cliente, &importe);
        
        printf("\nRecibi deposito. Cliente: %d | Importe: $%d | Remitente: %d\n", cod_cliente, importe, mensaje_recibido.int_rte);
        /*Chequeo que el cliente exista*/
        if (cod_cliente < 0 || cod_cliente >= 100) {
            printf("El cliente no existe\n");
            sprintf(respuesta, "%d|El cliente no existe", cod_cliente);
            enviar_mensaje(id_cola_mensajes, mensaje_recibido.int_rte, MENSAJE_A_BANCO, EVT_RTA_DEPOSITO_NOK, respuesta);
        /*Chequeo que el importe sea mayor a 0*/
        } else if (importe <= 0) {
            printf("El importe debe ser mayor a 0\n");
            sprintf(respuesta, "%d|El importe debe ser mayor a 0", cod_cliente);
            enviar_mensaje(id_cola_mensajes, mensaje_recibido.int_rte, MENSAJE_A_BANCO, EVT_RTA_DEPOSITO_NOK, respuesta);
        } else {
            /*Se hace el deposito*/
            saldos[cod_cliente] += importe;
            printf("  Deposito exitoso. Nuevo saldo: $%d\n", saldos[cod_cliente]);
            sprintf(respuesta, "%d|%d", cod_cliente, saldos[cod_cliente]);
            enviar_mensaje(id_cola_mensajes, mensaje_recibido.int_rte, MENSAJE_A_BANCO, EVT_RTA_DEPOSITO_OK, respuesta);
        }
    }
    else if (mensaje_recibido.int_evento == EVT_EXTRACCION) {
        sscanf(mensaje_recibido.char_mensaje, "%d|%d", &cod_cliente, &importe);
        
        printf("\nRecibi extraccion. Cliente: %d | Importe: $%d | Remitente: %d\n", cod_cliente, importe, mensaje_recibido.int_rte);
        /*Chequeo que el cliente exista*/
        if (cod_cliente < 0 || cod_cliente >= 100) {
            printf("El cliente no existe\n");
            sprintf(respuesta, "%d|Cliente no existe", cod_cliente);
            enviar_mensaje(id_cola_mensajes, mensaje_recibido.int_rte, MENSAJE_A_BANCO, EVT_RTA_EXTRACCION_NOK, respuesta);
        } else if (importe <= 0) {
            printf("El importe debe ser mayor a 0\n");
            sprintf(respuesta, "%d|El importe debe ser mayor a 0", cod_cliente);
            enviar_mensaje(id_cola_mensajes, mensaje_recibido.int_rte, MENSAJE_A_BANCO, EVT_RTA_EXTRACCION_NOK, respuesta);
        /*Chequeo que el saldo sea mayor a la extraccion*/
        } else if (saldos[cod_cliente] < importe) {
            printf("El saldo insuficiente (tiene $%d, quiere extraer $%d)\n", saldos[cod_cliente], importe);
            sprintf(respuesta, "%d|El saldo es insuficiente", cod_cliente);
            enviar_mensaje(id_cola_mensajes, mensaje_recibido.int_rte, MENSAJE_A_BANCO, EVT_RTA_EXTRACCION_NOK, respuesta);
        } else {
            /*Se hace la transaccion*/
            saldos[cod_cliente] -= importe;
            printf("  Extraccion exitosa. Nuevo saldo: $%d\n", saldos[cod_cliente]);
            sprintf(respuesta, "%d|%d", cod_cliente, saldos[cod_cliente]);
            enviar_mensaje(id_cola_mensajes, mensaje_recibido.int_rte, MENSAJE_A_BANCO, EVT_RTA_EXTRACCION_OK, respuesta);
        }
    }
    else {
        /*Numero de evento incorrecto*/
        printf("\nEvento desconocido: %d\n", mensaje_recibido.int_evento);
    }
}
void inicializar_saldos(int saldos[]) {
    int i;
    memset(saldos, 0, sizeof(saldos[CANTIDAD_CLIENTES]));
    for (i = 0; i < CANTIDAD_CLIENTES; i++) {
        saldos[i] = 10000;
    }
}


int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    int saldos[CANTIDAD_CLIENTES];
    Mensaje mensaje_recibido;

    inicializar_saldos(saldos);
    /*Inicializamos y limpiamos la cola de mensajes*/
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);
    inEscribirArchivo("bancoInicializado.dat", "1\n");    


    while (1) {
        printf("Banco esperando mensajes\n");
        recibir_mensaje(id_cola_mensajes, MENSAJE_A_BANCO, &mensaje_recibido);
        procesar_mensajes(id_cola_mensajes, mensaje_recibido, saldos);
    }
    borrar_cola_de_mensajes(id_cola_mensajes);
    return 0;
}
