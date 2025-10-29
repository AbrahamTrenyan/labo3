

Proceso ARQUERO (MSG_ARQUERO)
1. Borrar los mensajes anteriores, para empezar de 0.
2. Espera recibir EVT_TIRO de cada pateador.
3. Selecciona al azar un evento (EVT_PALO, TRAVESAÑO, GOL o FUERA).
4. Espera 500 ms.
5. Envía el evento seleccionado en el punto 3 al pateador (remitente).
6. Una vez recibidos 5 tiros (en total) finaliza y muestra la cantidad de goles recibidos y el número de pateador de los que los hicieron. Si no se llega a 5 tiros, vuelve al punto 2 (es un tiro por pateador).

Proceso PATEADORES
El hilo principal (main):
• Lanza 5 hilos HiloPateador, uno por pateador (son 5 pateadores).
• Se queda esperando que terminen los hilos.
• Al finalizar los hilos se debe mostrar la cantidad de goles.
Además, emitir un listado con NRO_PATEADOR, RESULTADO_TIRO (GOL, TRAVESAÑO, FUERA, PALO) (uno por cada uno).


HiloPateador (para ordenar los tiros se utiliza un mutex)
1. Espera obtener el MUTEX.
2. Espera 500 ms.
3. 4. Envía EVT_TIRO a MSG_ARQUERO (un solo tiro por pateador).
Espera recibir un evento del proceso ARQUERO.
• Si recibe un mensaje EVT_GOL, escribe por pantalla “GOOOOOL”.
• Si recibe cualquier otro evento, escribe por pantalla “UFFFFF”.
5. Finaliza devolviendo el resultado.
