Tema: Threads
- Se ejecuta el ejemplo del pdf del uso de threads en el main.c
gcc -Wall -pedantic-errors -std=gnu89 -O3 -Wdeclaration-after-statement -pthread -I./ main.c
./a.out

- Ejercicio resuelto en clase:
Consigna
Implementar un programa que reciba a través de argumentos 1 o más números enteros. Cada uno de estos números deberá ser utilizado para determinar los N primeros números primos. 
Se deberán lanzar tantos thread como números ingresados. Cada thread deberá devolver la sumatoria de los N números primos calculados. Al finalizar, se deberá realizar una sumatoria total del resultado de cada thread.
Implementar la solución con thread y calcular el tiempo empleado en el cálculo total, comparar este tiempo con una solución estándar sin thread, es decir, realizando cada cálculo en forma secuencial (un
sólo hilo). Los tiempos deberán tener una precisión del orden de los milisegundos
