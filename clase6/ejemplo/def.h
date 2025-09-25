#define CANTIDAD 10
#define CANTIDAD_TOTAL 10
#define DESDE 0
#define HASTA 25
#define TRUE 1
#define FALSE 0
#define LARGO 150
#define COMANDO "/bin/ls"     /*Comando conocido para ftok()*/
#define ENTERO 10             /*Entero para ftok()*/
#define ARCHIVO "archivo.dat" /*Nombre del archivo de almacenamiento*/
#define CLAVE_BASE 33         /*Clave base para semaforos*/
#define MS 1000               /*Multiplicar usleep() por la cantidad de ms requerida*/
typedef struct tipo_dato dato;
struct tipo_dato
{
    int numero;
    char letra;
};
