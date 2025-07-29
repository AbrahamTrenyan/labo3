#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define CANTIDAD 10
#define DESDE 0
#define HASTA 10
int main(int argc, char *argv[])
{
int desde = DESDE;
int hasta = HASTA;
int n,num;

if(argc==3)
{
desde = atoi(argv[1]);
hasta = atoi(argv[2]);
}
printf("cantidad = %d desde = %d hasta = %d \n",CANTIDAD, desde, hasta);
srand(time(NULL)); /* semilla para el generador de numeros aleatorios */

for (n=0; n<CANTIDAD;n++)
{
num = (rand()%(hasta-desde+1))+desde;/* genera un numero aleatorio entre desde y hasta */
printf("el numero es %d \n", num);
}

return 0;
}
