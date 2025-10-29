#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "funciones.h"
#include "archivos.h"
#include "global.h"
#include "unistd.h"

int devolverNumeroAleatorio(int minimo, int maximo)
{
    int numeroAleatorio = 0;


    numeroAleatorio = rand() % (maximo - minimo + 1) + minimo;

    return numeroAleatorio;

}

void generarNumerosNoRepetidos(int *array, int topeBucle, int minimo, int maximo)
{
    int i, j;
    int repetido = 0;
    int numeroAleatorio = 0;

    
    for(i = 0; i < topeBucle; i++)
    {
        repetido = 1;
        while(repetido == 1)
		{
			numeroAleatorio = devolverNumeroAleatorio(minimo, maximo);
			repetido = 0;
			for(j = 0; j < i; j++)
			{
				if(numeroAleatorio == array[j])
                {
                    repetido = 1;
                    break;
                }
					
			}
		}
		array[i] = numeroAleatorio;

    }

}

void activarFlag(void)
{

    if(abrirArchivo("flag.txt", "w") == TRUE)
    {
        escribirArchivo("start");

        cerrarArchivo();
        printf("\nFlag creado\n");
    } else
    {
        printf("\nError al crear Flag\n");
        exit(EXIT_FAILURE);
    }
    

}

void esperarFlag(void)
{

    while(abrirArchivo("flag.txt", "r") == FALSE)
    {
        usleep(500000);

    }

    cerrarArchivo();

}



