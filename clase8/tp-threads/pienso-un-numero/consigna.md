Ejercicio 01: “Pienso un número”
En base a la siguiente información:
Se trata de un proceso PIENSOUNNUMERO con varios hilos (uno por jugador).
El hilo principal (main):
• Recibe por parámetro la cantidad de jugadores (argc, argv).
• “Piensa un número” genera en forma aleatoria un número del 1 al 99.
• Inicializa una variable int alguien_acerto = 0 (local del main)
• Lanza tantos ThreadJugadores como jugadores se hayan ingresado por parámetro; les pasa
como parámetro el número que “pensó”. Además, le pasa el puntero a la variable
alguien_acerto.
• Queda a la espera que los hilos finalicen.
• Al finalizar los hilos, el main debe indicar cuál es el jugador ganador.
ThreadJugadores (uno por Jugador):
1. Cada N ms (N aleatorio en 500 a 5000) genera un número al azar de 1 al 99 (no repetitivos).
2. Verifica la variable alguien_acerto (puntero que recibió por parámetro); si ésta es distinta de 0,
significa que ya hay un ganador. En dicho caso, termina el hilo.
3. Compara el número generado con el que “pensó” el main (el que recibió por parámetro).
4. En caso de acierto, cambia el valor de la variable alguien_acerto (utilizando el puntero) por el
número de jugador. Y termina el hilo.
5. Al finalizar el hilo, cada uno debe devolver la cantidad de intentos que tuvo.


Realizar los siguientes puntos:
1. Generar los hilos y sólo utilizar como variable global la de mutex. Todas las demás deben ser pasadas como parámetro desde el main al hilo.
2. Al finalizar el main, debe mostrar al ganador y mostrar la cantidad de intentos de cada
jugador.
3. Evitar que haya más de un ganador.
4. Mostrar la actividad en forma diferenciada de cada hilo
