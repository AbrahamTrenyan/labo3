Examen Segundo parcial
Consignas 

La Carrera Espiral:

En una carrera circular, con forma de espiral, 2 mosquitos compiten por sobrevivir. 
El espiral tiene una distancia de 95 metros. Este valor (95) debe enviarse de un proceso (el inicializador seguramente) a otro usando memoria compartida.
Los mosquitos quieren llegar a la meta antes que el humo los alcance.

Aún así, es una carrera por turnos (todos tienen que terminar sus turnos si quieren sobrevivir). Los mosquitos avanzan de entre 3 y 6 metros, mientras que el humo avanza entre 1 y 4 metros (estos valores que van saliendo son aleatorios). Si el humo supera alguno de los mosquitos, es que ese mosquito no sobrevivió y no continua la carrera. 

Se cuenta con 2 procesos. Todo el tiempo deben mostrarse los eventos y lo que va aconteciendo en los dos procesos. Lo recomendable sería contar con el proceso panel/tablero, y por otro lado proceso jugadores/mosquitos y humo. 

Panel/tablero: debe informar lo que sucede luego de que un mosquito avance, el humo avance, y/o no sobrevivan o lleguen a destino. Pero siempre informar por turno, no solo una vez al final.
 
Debe utilizar Threads, cola de mensajes para la comunicación,  mutex para el sincronismo. 

Cada 300ms el sistema debe estar interactuando un nuevo turno.
Usar los eventos que crea necesario y las variables y estructuras que precise. 
Borrar los mensajes anteriores, para empezar de 0. 
Se debe mostrar lo que sucede en los dos procesos en todo momento, y cual jugador gano y el resultado.
Debe utilizar archivos, para que pueda ejecutarse cualquier proceso primero.
Se recomienda que deba comenzar la carrera presionando una tecla.






