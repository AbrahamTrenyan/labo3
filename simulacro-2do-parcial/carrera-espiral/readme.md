Tengo dos procesos, tablero y jugadores.

El proceso tablero es quien maneja los turnos de cada jugador, y es el que informa 
si alguno fue eliminado, y la vida que tiene cada uno. 
Tiene un array de struct donde lleva toda esa informacion.

El proceso juadores lanza 3 threads jugador, que solo conocen su id, y id de cola de mensajes. 
Con la cola de mensajes se comunican con el tablero, que les va indicando si es su turno. Cuando es su turno ellos procesan su avance dependiendo de si son mosquitos o humo y se lo envian al tablero por cola de mensajes.
De esta manera el mensaje turno tiene dos sentidos, cuando el tablero se lo envia a
los jugadores les indica que deben avanzar, y cuando lo recibe, lleva la cantidad de metros que saco el jugador.
El tablero procesa si alguno llego a la meta o fue eliminado.

Se debe correr primero el proceso tablero, y despues el proceso equipos.
Hay un archivo flag que indica si se corrio o no el proceso tablero, de no ser asi corta la ejecucion de jugadores.
Al correr Make se borra este archivo flag.
