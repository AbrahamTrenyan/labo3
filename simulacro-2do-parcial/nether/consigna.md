Examen Segundo parcial
Consignas 

Nether:
En un mundo distante, el Nether, hay un guerrero llamado Steve, que pelea contra monstruos de este mundo.

Steve tiene que hacer 100 pasos para llegar a su mundo.
Esta información (o sea el total de pasos que esta del inicio hasta el portal es de 100 pasos) se debe compartir con memoria compartida, del tablero a los jugadores. 

Steve hace de 2 a 8 pasos por vuelta (aleatorio). 
Pero como se comento, hay monstruos, en diversas partes de su recorrido.

-A los 20 pasos (si Steve cae ahí o supera los 20 pasos) se encuentra un zombie, que pelea contra Steve, (aleatorio de 1 a 4), si sale 4, gana el zombie, Steve muere y se termina el juego, sino, Steve continua

-A los 45 pasos (si Steve cae ahí o supera los 45 pasos) se encuentra un creeper que pelea contra Steve, (aleatorio de 1 a 3), si sale 3, gana el creeper, Steve muere y se termina el juego, sino continua.


Pero también hay un Piglin, monstruo que corre junto a él, y si llega primero a la meta, cierra el portal para que vuelva a su casa, y Steve muere. El Piglin camina entre 1 a 6 pasos.

Se cuenta con 2 procesos. Todo el tiempo deben mostrarse los eventos y lo que va aconteciendo en los dos procesos. Lo recomendable sería contar con el proceso panel/tablero, y por otro lado proceso jugadores. 

Panel/tablero: debe informar lo que sucede luego de que Steve va avanzando, sus pasos y lo que acontece con los monstruos, lo mismo el Piglin. Pero siempre informar por turno, no solo una vez al final.
 
Debe utilizar Threads, cola de mensajes para la comunicación,  mutex para el sincronismo. 

Cada 400ms el sistema debe estar interactuando un nuevo turno.
Usar los eventos que crea necesario y las variables y estructuras que precise. 
Borrar los mensajes anteriores, para empezar de 0. 
Se debe comenzar el juego utilizando un archivo flag con un bucle (o sea cualquiera de los dos procesos debería poder ejecutarse primero). 


 

