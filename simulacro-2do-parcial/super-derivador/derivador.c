#include "def.h"
#include "funciones.h"
#include "global.h"
#include "memoria.h"
#include "mensajes.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "archivos.h"



int main(int argc, char *argv[])
{
    int id_cola_mensajes;
/*     int id_memoria;
 */ /* int *memoria = NULL; */
    int done = 0;
    int  i = 0;
    int id_caja = 0;
    Mensaje mensaje;
    Productos productos[MAX_PRODUCTOS];
    int cant_productos = 0;
    int precio_total = 0;
    char input[100];
    memset(productos, 0, sizeof(productos));
    memset(&mensaje, 0, sizeof(mensaje));


    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);


    inEscribirArchivo(ARCHIVO_FLAG, "1\n");
    printf("Super derivador inicializado\n");

    /*Inicializo los jugadores*/
    for (i = 0; i < 4; i++) {
        sprintf(productos[i].descripcion, "Producto %d", i);
        productos[i].precio = inDevolverNumeroAleatorio(1, 100);
    }


    /* memoria = creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    *memoria = VIDA_INICIAL;
    printf("La cantidad de vida inicial es de %d, se les informa a los hilos por memoria compartida\n", *memoria); */


    srand(time(NULL));
    
    for (i = 0; i < CANT_CAJAS; i++) {
        enviar_mensaje(id_cola_mensajes, MSG_CAJA + i, MSG_DERIVADOR, EVT_INICIO, productos[i].descripcion);
    }
    
    while (done == 0) {
        printf("------------------------------------\n");
        printf("Ingrese la cantidad de productos, - para finalizar: ");
        scanf("%s", input);
        
        if (strcmp(input, "-") == 0) {
            done = 1;
        } else {
            cant_productos = atoi(input);
            
            if (cant_productos <= 0) {
                printf("No hay productos ingresados.\n");
                continue;
            }
            derivar(cant_productos, &id_caja);
            precio_total = 0;
            
            for (i = 0; i < cant_productos; i++) {
                printf("Ingrese el nombre del producto: ");
                scanf(" %[^\n]", productos[i].descripcion);
                printf("Ingrese el precio del producto: ");
                scanf("%d", &productos[i].precio);
                precio_total += productos[i].precio;
            }
            sprintf(mensaje.char_mensaje, "%d", precio_total);
            enviar_mensaje(id_cola_mensajes, MSG_CAJA + id_caja, MSG_DERIVADOR, EVT_ATENDER_CLIENTE, mensaje.char_mensaje);
        }
    }
    /*Notifico a las cajas que el sistema terminó*/
    for (i = 0; i < CANT_CAJAS; i++) {
        sprintf(mensaje.char_mensaje, "Caja %d terminada", i);
        enviar_mensaje(id_cola_mensajes, MSG_CAJA + i, MSG_DERIVADOR, EVT_FIN, mensaje.char_mensaje);
    }
    
    sleep(1);
    printf("Super derivador terminado\n");
    borrar_cola_de_mensajes(id_cola_mensajes);
    return 0;
}
