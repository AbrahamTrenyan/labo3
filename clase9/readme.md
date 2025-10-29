Tema: Multithreading
El proceso inicializador borra la cola de mensajes al principio.
Tenemos que tener:
Flag que chequea que se incializo el semaforo.
Framework memoria compartida.
De ahora en mas vamos a tener dos procesos, uno multihilo.
El bucle del thread va a tener gralmente 
una funcion recibir mensaje bloqueante, despues bloquea el mutex, hace lo que tiene que hacer, libera el mutex, usleep y se vuelve a ejecutar.
La tortuga y la liebre podrian saber cuando tienen que parar y el tablero solo recibiria(para el 2do parcial se puede ser unidireccional)
