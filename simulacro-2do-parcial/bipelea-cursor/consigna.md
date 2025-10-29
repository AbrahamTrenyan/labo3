BiPelea:

En un futuro no muy distante, se realiza una lucha entre bandos, dual. O sea es un equipo de dos participantes por equipo. 
Cada equipo peleará para lograr conseguir el trofeo y a veces salvar su vida. 
Cada uno de los luchadores tiene como valor nominal 1200 de vida. (ESTE VALOR DEBE SER COMPARTIDO DE UN PROCESO INICIAL AL OTRO, USANDO MEMORIA COMPARTIDA)

Es una batalla por turnos. En cada turno, restaran de 8 a 27 de vida de los oponentes (valor aleatorio).  Pero en esta pelea, en cada turno cae un arma, lo que hace que pueda sumarse el valor de ataque (valor de arma aleatorio por vez de 1 a 2):
1-Cuchillo (aumenta golpe en 6)
2-Manopla (aumenta golpe en 8)
En el turno, el luchador envía por mensaje, la cantidad de puntos del golpe (a los otros 2 oponentes), pero al recibir el golpe el oponente, sale un número aleatorio (1 a 2) que informa si acertó el golpe (resta el total de puntos del golpe a ese oponente) o si no lo acertó no le resta nada. 



Se contará con un array (arreglo) de estructuras, en la que cada estructura cuenta con el nombre del luchador (puede también ingresarse por teclado en menú) y su vida.

Deberá realizar dos procesos, donde usted decidirá si será un proceso de un equipo y otro proceso el otro equipo o si realiza dos procesos (Recomendado, uno para equipos y otro para ring/cancha por ejemplo). Para comunicar debe utilizar  cola de mensajes (por ejemplo MSJ_LUCHADOR+i , ó el nombre de los luchadores que se sabe que son 4).

Se debe informar que luchadores ganaron o perdieron, y cuales salen invictos en todo momento, en los procesos. 

Se debe mostrar la actividad de cada proceso.
Usar los eventos que crea necesario. 

Debe utilizar archivos, para que pueda ejecutarse cualquier proceso primero.

Pensar bien que/quien es cada proceso! Comenzar por lo mínimo, lo más importante es que compile, el sincronismo y que comunique!.

