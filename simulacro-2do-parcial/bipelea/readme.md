Tengo dos procesos, ring y equipos.

El proceso ring es quien maneja los turnos de cada jugador, y es el que informa 
si alguno fue eliminado, y la vida que tiene cada uno. 
Tiene un array de struct donde lleva toda esa informacion.

El proceso equipos lanza 4 threads jugador, que solo conocen su id, nombre, y id de cola de mensajes. Con la cola de mensajes se comunican con el ring, que les va indicando si es su turno. Cuando es su turno ellos procesan su golpe y se lo envian al ring por cola de mensajes.
De esta manera el mensaje golpe tiene dos sentidos, cuando el ring se lo envia a
los jugadores les indica que deben atacar, y cuando lo recibe, lleva la cantidad de puntos que saco el jugador.

Se debe correr primero el proceso ring, y despues el proceso equipos.
Hay un archivo flag que indica si se corrio o no el proceso ring, de no ser asi corta la ejecucion de equipos.
Al correr Make se borra este archivo flag.
