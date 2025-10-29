La carrera animal:
Se juega una carrera entre distintas especies de animales.
En esta carrera corre un conejo, un gato y un perro. Es una carrera por pasos, donde el conejo avanza entre 4 a 9 (donde la cantidad de pasos se elije aleatoriamente entre estos valores), el gato avanza entre 1 y 10 pasos y el perro avanza entre 3 y 8.


La carrera termina con el primer animal que llega a 117 pasos, o sea a la meta. Si los tres superan esta cantidad en la misma cantidad de veces que dieron pasos, es empate.
Este valor (117) debe pasarse del proceso de inicialización al otro, mediante memoria compartida.


Se debe utilizar threads, cola de mensajes, y para el sincronismo usar mutex.
Pueden ser un proceso por animal,o quizás le conviene más que sean dos procesos, uno de los procesos sea pista/tablero/cancha y el otro proceso sean los animales(threads).


Puede utilizar los siguientes destino y eventos, o los que usted elija.


typedef enum {
     MSG_NADIE,     |//0
     MSG_PISTA,     //1
     MSG_JUGADOR1, // 2
     MSG_JUGADOR2, // 3
     MSG_JUGADOR3, // 4
} Destinos;


typedef enum {
EVT_NINGUNO, //0 
EVT_CORRO, //1
EVT_FIN, //2 
} Eventos; //Podria tener el EVT_INICIO tmb.
	
Se debe mostrar lo que sucede en los dos procesos en todo momento, y cual jugador gano y el resultado.
Debe utilizar archivos, para que pueda ejecutarse cualquier proceso primero.
Se recomienda que deba comenzar la carrera presionando una tecla.
