#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "archivos.h"
#include "def.h"
#include "global.h"
FILE *ptrFile; /*se puede/debe declarar el puntero para el uso de archivos, global de archivo*/
int inAbrirArchivo(char *szNombreArchivo, char *szModo)
{
    ptrFile = fopen(szNombreArchivo, szModo);
    if (ptrFile == NULL)
        return FALSE;
    return TRUE;
}
void voCerrarArchivo()
{
    fclose(ptrFile);
}
int inLeerArchivo(char *szBuffer)
{
    /*Se puede colocar una validación, sobre la lectura*/
    if (fscanf(ptrFile, "%s", szBuffer) != 1)
        return FALSE;
    fscanf(ptrFile, "%s", szBuffer); /*Se puede optimizar siendo mas certeros en el buffer*/
    return TRUE;
}
int inEscribirArchivo(char *szDatos)
{
    int inRes = 0;
    inRes = fprintf(ptrFile, "%s", szDatos);
    if (inRes < 0)
        return FALSE;
    return TRUE;
}
void escribirEmpleados()
{
    Empleado emp;
    char buffer[100 + 1];
    int continuar = 1;
    if (!inAbrirArchivo("empleados.txt", "w"))
    {
        printf("No se pudo abrir el archivo para escritura.\n");
        return;
    }
    while (continuar)
    {
        printf("Ingrese nombre: ");
        scanf("%s", emp.nombre);
        printf("Ingrese legajo: ");
        scanf("%d", &emp.legajo);
        printf("Ingrese sueldo: ");
        scanf("%d", &emp.sueldo);
        sprintf(buffer, "%s %d %d\n", emp.nombre, emp.legajo, emp.sueldo);
        if (!inEscribirArchivo(buffer))
        {
            printf("Error al escribir en archivo.\n");
        }
        printf("¿Desea ingresar otro empleado? (1: Sí, 0: No): ");
        scanf("%d", &continuar);
    }
    voCerrarArchivo();
}
void leerEmpleados()
{
    char linea[100 + 1];
    char nombre[50 + 1];
    int legajo;
    int sueldo;
    if (!inAbrirArchivo("empleados.txt", "r"))
    {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }
    while (!feof(ptrFile))
    {
        if (inLeerArchivo(linea) == TRUE)
        {
            printf("Línea leída: %s\n", linea);
            /*Se puede cargar en variables por los espacios, usando sscanf*/
            if (sscanf(linea, "%s %d %d", nombre, &legajo, &sueldo) == 3)
            {
                printf("Nombre: %s | Legajo: %d | Sueldo: %d\n", nombre, legajo, sueldo);
            }
        }
    }
    voCerrarArchivo();
}
