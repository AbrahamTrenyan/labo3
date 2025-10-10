TP Banco-Cajero con Cola de Mensajes


Consta de dos procesos:
- banco: Maneja saldos de 100 clientes (codigos 0-99). Inicializa la cola de mensajes y los datos de los clientes
- cajero: Realiza operaciones bancarias (consulta, deposito, extraccion) comunicandose con el banco con cola de mensajes y los eventos de la consigna.

Compilacion:
make

Ejecucion:
Ejecutar PRIMERO en terminal 1: ./banco
Ejecutar en terminal 2, 3, etc: ./cajero [NUMERO]

Ejemplo: ./cajero 100

Se pueden ejecutar varios cajeros simultaneamente con diferentes numeros (100, 101, 102, etc). Cada peticion del cajero al banco se procesa en el orden de la cola de mensajes por lo que se garantiza la sincronizacion.

Se añadio la validacion para que al ejecutar primero el cajero, salte un error. Se hace mediante un archivo banco inicializado que se borra en cada compilacion.
