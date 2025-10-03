    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include "def.h"
    #include "global.h"
    #include "semaforos.h"
    #include "archivos.h"
    #include "funciones.h"

    void procesar_pedido(char *nombreArchivo, int nroCaja, char *buffer)
    {
        /* Verifico si existe el archivo y leo su contenido */
        if(inExisteArchivo(nombreArchivo)) {
            if(inAbrirArchivo(nombreArchivo, "r")) {
                /* Si hay contenido, leo */
                memset(buffer, 0, sizeof(buffer));
                if(inLeerArchivo(buffer)) {
                    printf("=== CAJA %d ===\n", nroCaja);
                    
                    printf("Producto\tPrecio\n");
                    printf("%s", buffer);
                    while(inLeerArchivo(buffer)) {
                        printf("%s", buffer);
                    }
                    printf("=== FIN DEL PEDIDO ===\n\n");
                    voCerrarArchivo();
                    if(inAbrirArchivo(nombreArchivo, "w")) {   
                        /*vacía el archivo para el proximo cliente*/
                        voCerrarArchivo();
                        printf("Esperando proximo cliente\n");
                    } else {
                        printf("No se pudo vaciar el archivo %s\n", nombreArchivo);
                    }
                } else {
                    voCerrarArchivo();
                }
            } else {
                printf("Error: No se pudo abrir el archivo %s\n", nombreArchivo);
            }
        }
    }
    void obtener_numero_caja(int argc, char *argv[], int *nroCaja)
    {
        /*Verifico que se haya ingresado el numero de caja*/
        if(argc != 2) {
            printf("Ingresa como parametro el numero de la caja\n");
            exit(1);
        }
        
        *nroCaja = atoi(argv[1]); 
        if(*nroCaja < 1 || *nroCaja > CANT_CAJAS){
            printf("El nro de caja debe ser entre 1 y %d.\n", CANT_CAJAS);
            exit(1);
        }
    }

    void derivar(int cant_productos, int *nroCaja)
    {    
        if(cant_productos == 0){
            printf("No hay productos ingresados\n");
            exit(1);
        }else if(cant_productos > 0 && cant_productos <= 5){
            *nroCaja = 1;
        }else if(cant_productos >= 6 && cant_productos <= 10){
            *nroCaja = 2;
        }else if(cant_productos >= 11 && cant_productos <= CANT_MAX_PRODUCTOS){
            *nroCaja = 3;
        }
        else{
            printf("Excedió el numero de productos\n");
            exit(0);
        }
    }


