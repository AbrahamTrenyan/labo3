Examen Segundo Parcial
Consignas
MonoNopoly:
Se juega a un juego clásico, financiero, el MonoNopoly.
En este juego la cantidad de jugadores se pasará por parámetro.
Se contará con una pista, que tendrá 60 pasos. Cada jugador por vuelta, de manera aleatoria, hara los pasos, los cuales van de 0 a 3 (siendo 0 que no avanza).
Cada jugador empieza con $1000, los cuales se deben enviar desde un proceso a otro, usando memoria compartida. 
En el tablero del juego, que va desde la posición de inicio (0) siendo la primera la (1), hasta la (60), cada posición puede tener diversas recaudaciónes o recompensas. Si pierde todo su dinero, pierde el jugador, siguen los demas:
Posición 3: Compra caramelos, pierde $5
Posición 4: Cuota de la universidad, pierde $100
Posición 6: Impuestos, pierde $200
Posición 7: Cumple años, recibe $150
Posición 9: Paga la jubilación, pierde $40
Posición 14: Entra a la cárcel, pierde un turno.
Posición 15: Choca el auto, pierde $400
Posición 18: Realiza un trabajo, gana $300
Posición 19: Le roban, pierde $600
Posición 23: Gana la lotería, gana $800
Posición 25: Vende un sillón, gana $75
Posición 28: Pierde la billetera, pierde $340
Posición 31: Bitcoin baja, pierde $120
Posición 34: Bitcoin sube, gana $120
Posición 37: Se compra un auto, pierde $1000
Posición 39: Vende el auto, gana $500
Posición 45: Se casa, pierde $400
Posición 48: Compra comida, pierde $15
Posición 51: Vende la tele, gana $50
Posición 53: Pierde un turno
Posición 54: Hace otro trabajo, gana $300
Posición 55: Recibe $100. 
Ultima posición, si la pasa termino.

El jugador que termina con más dinero gana el juego.
Se debe utilizar threads, cola de mensajes, y para el sincronismo usar mutex.
Pueden ser 2 procesos. Uno de los procesos sea pista/tablero/panel y el otro proceso sean los jugadores(threads).

Se debe mostrar lo que sucede en los procesos en todo momento, y cual jugador gano, el dinero y el resultado.
Debe utilizar archivos, para que pueda ejecutarse cualquier proceso primero.
Se puede hacer que comience la carrera presionando una tecla.
Pensar bien que/quien es cada proceso! Comenzar por lo mínimo, lo más importante es el sincronismo y que compile!.
