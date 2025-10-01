Centro de logística con control de bebidas:

Se realizó el ejercicio siguiendo el esquema productor/consumidor, en este caso el 
derivador es el productor y es quien inicializa el semáforo, por lo tanto se ejecuta primero. 

Cada sistema procesa las bebidas que le fueron asignadas, leyendo su archivo y mostrando la información formateada.

Compilar: make (hace un clean de los archivos anteriores)
Ejecutar cada proceso en una terminal en este orden (el orden de los procesos sistemas es indistinto): 
1. ./derivador
2. ./sistema a
3. ./sistema b
4. ./sistema c

