#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "global.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"

void procesar_deposito(int importe, int tipo_pago, int cajero)
{
    int indice_cajero;
    indice_cajero = cajero - 1;
    
    if (tipo_pago == 1) {  /* Efectivo */
        total_efectivo++;
        total_importe_efectivo += importe;
        cajeros_efectivo[indice_cajero]++;
        cajeros_importe_efectivo[indice_cajero] += importe;
    } else {  /* Cheque */
        total_cheque++;
        total_importe_cheque += importe;
        cajeros_cheque[indice_cajero]++;
        cajeros_importe_cheque[indice_cajero] += importe;
    }
    printf("Deposito procesado: Cajero %d - $%d %s\n", cajero, importe, 
           (tipo_pago == 1) ? "efectivo" : "cheque");
}

void mostrar_resumen_total(void)
{
    printf("\nTOTAL\n");
    printf("TC-EFEC T$-EFEC TC-CHEQ T$-CHEQ\n");
    printf("%-7d $%-6d %-7d $%d\n", total_efectivo, total_importe_efectivo, 
           total_cheque, total_importe_cheque);
}

void mostrar_resumen_cajero(int cajero)
{
    int indice_cajero;
    indice_cajero = cajero - 1;
    printf("CAJERO%d\n", cajero);
    printf("TC-EFEC T$-EFEC TC-CHEQ T$-CHEQ\n");
    printf("%-7d $%-6d %-7d $%d\n", 
           cajeros_efectivo[indice_cajero], cajeros_importe_efectivo[indice_cajero],
           cajeros_cheque[indice_cajero], cajeros_importe_cheque[indice_cajero]);
}

void generar_depositos_aleatorios(int cajero)
{
    int num_depositos;
    int i;
    int importe;
    int tipo_pago;
    char linea[MAX_LINEA];
    char nombre_archivo[50];
    
    num_depositos = inDevolverNumeroAleatorio(MIN_DEPOSITOS, MAX_DEPOSITOS);
    sprintf(nombre_archivo, "cajero%d.dat", cajero);
    
    if (!inAbrirArchivo(nombre_archivo, "a")) {
        printf("Error: no se puede crear/abrir el archivo %s\n", nombre_archivo);
        return;
    }
    
    printf("Cajero %d generando %d depositos\n", cajero, num_depositos);
    
    for (i = 0; i < num_depositos; i++) {
        importe = inDevolverNumeroAleatorio(IMPORTE_MIN, IMPORTE_MAX);
        tipo_pago = inDevolverNumeroAleatorio(0, 1);
        sprintf(linea, "%d %d\n", importe, tipo_pago);
        inEscribirArchivo(linea);
    }
    
    voCerrarArchivo();
    printf("Lote del cajero %d creado con %d depositos\n", cajero, num_depositos);
}

int inDevolverNumeroAleatorio(int inDesde, int inHasta)
{
    if (inDesde > inHasta)
    {
        return -1;
    }
    return (rand() % (inHasta - inDesde + 1)) + inDesde;
}
