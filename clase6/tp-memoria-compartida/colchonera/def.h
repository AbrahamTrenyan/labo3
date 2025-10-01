#define CANTIDAD 10
#define DESDE 1
#define HASTA 99
#define TRUE 1
#define FALSE 0
#define LARGO 150
#define COMANDO "/bin/ls"     /*Comando conocido para ftok()*/
#define ENTERO 10             /*Entero para ftok()*/
#define CLAVE_BASE 33         /*Clave base para semaforos*/
#define MS 1000               /*Multiplicar usleep() por la cantidad de ms requerida*/
typedef struct descripcion descripcion;
struct descripcion
{
int codigo;
int cantidad;
char nombre[LARGO];
};
