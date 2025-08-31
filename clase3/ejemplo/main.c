#include <stdio.h>
#include <stdlib.h>
#include "archivos.h"
#include "def.h"
typedef struct
{
    char nombre[50];
    int legajo;
    int sueldo;
} Empleado;
int main(int argc, char *argv[])
{
    escribirEmpleados();
    printf("\n=== Datos leídos del archivo ===\n");
    leerEmpleados();
    return 0;
}
