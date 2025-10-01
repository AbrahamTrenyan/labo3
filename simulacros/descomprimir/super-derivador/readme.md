Se realizó el ejercicio siguiendo el esquema productor/consumidor, en este caso el 
derivador es el productor y es quien inicializa el semaforo, por lo tanto se ejecuta primero. Elige que caja le corresponde y escribe en el archivo de esa caja. 
El proceso caja se ejecuta con parametros 1, 2 o 3 para saber que caja es. Obtiene el semaforo y lee el archivo con su nombre y su parametro.

Compilar: Make(hace un clean de los archivos anteriores)
Ejecutar cada proceso en una terminal en este orden(el de los procesos caja es indistinto): 
1. ./derivador
2. ./caja 1
3. ./caja 2
4. ./caja 3
