Consigna
Resolver los siguientes ejercicios:
Ejercicio 1: Ruleta rusa
Se trata de un proceso REVOLVER y otro JUGADORES con varios hilos (uno por cada jugador).
Utiliza cola de mensajes con los siguientes IDs:
MSG_NADIE 0
MSG_REVOLVER 1
MSG_JUGADOR 2(+nro_JUGADOR)
Eventos:
EVT_NINGUNO 0
EVT_INICIO 1
EVT_DISPARO 2
EVT_SALVADO 3
EVT_FIN 4
Proceso REVOLVER: (MSG_ REVOLVER)
Hilo Principal (main):
1- La cantidad de jugadores es siempre 6.
2- Borrar los mensajes anteriores para empezar de 0.
3- Elije, en forma aleatoria, un número del 1 al 6 y lo guarda en memoria local.
4- Le envía un mensaje a cada JUGADOR, EVT_INICIO. (MSG_JUGADOR+i).
5- Espera recibir mensajes de los JUGADORES.
EVT_DISPARO, NUMERO_ELEGIDO.
• Si NUMERO_ELEGIDO recibido es diferente al número del punto 3, contesta al JUGADOR
con EVT_SALVADO. (msg.int_rte). Sigue con el punto 6.
• Si NUMERO_ELEGIDO recibido es igual al número del punto 3, el “juego” finaliza; se envía un
mensaje EVT_FIN, NRO_JUGADOR (“eliminado”) a todos los JUGADORES
(MSG_JUGADOR+i). Sigue con el punto 7.
6- Repite desde el punto 5.
7- Finaliza

Proceso JUGADORES:
El hilo principal (main):
• La cantidad de jugadores es siempre 6.
• Genera un vector de 6 posiciones inicializado en 0, llamado “vector_tambor”, [0][0][0][0][0][0].
Este vector simula la posición de cada bala.
• Lanza tantos HiloJUGADOR como JUGADORES haya, y les pasa un puntero con la dirección
del “vector_tambor”.
• Se queda esperando que terminen los hilos.
• Muestra el número del JUGADOR “eliminado” por pantalla (recibido de los hilos).


HiloJUGADOR (uno por JUGADOR): (MSG_JUGADOR+nro_JUGADOR)
Para evitar que todas disparen juntas se deberá usar un MUTEX.
1- Espera recibir el mensaje EVT_INICIO.
2- Escribir por pantalla, “Soy el jugador N y voy a dispararme“
3- Envía al REVOLVER el EVT_DISPARO, NUMERO_ELEGIDO; este número lo saca del
“vector_tambor”, de uno por vez (es decir, donde no hay un 0), después pone esa posición en 1.
vector_tambor=>[1][0][0][0][0][0].
4- Escribir por pantalla, “Soy el jugador N y la posición del tambor es M“
5- Espera recibir mensajes del REVOLVER.
6- SI recibe un mensaje EVT_SALVADO.
Si recibe un mensaje EVT_FIN, devuelve el número del JUGADOR “eliminado” al main.
7- Devuelve si se “salvó” o fue “eliminado” y termina
