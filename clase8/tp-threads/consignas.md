Consignas
Ejercicio 01: “Pienso un número”
En base a la siguiente información:
Se trata de un proceso PIENSOUNNUMERO con varios hilos (uno por jugador).
El hilo principal (main):
• Recibe por parámetro la cantidad de jugadores (argc, argv).
• “Piensa un número” genera en forma aleatoria un número del 1 al 99.
• Inicializa una variable intalguien_acerto = 0 (local del main)
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
1. Generar los hilos y sólo utilizar como variable global la de mutex. Todas las demás deben ser
pasadas como parámetro desde el main al hilo.
2. Al finalizar el main, debe mostrar al ganador y mostrar la cantidad de intentos de cada
jugador.
3. Evitar que haya más de un ganador.
4. Mostrar la actividad en forma diferenciada de cada hilo.





Ejercicio 02: “Bingo”
En base a la siguiente información:
Un BINGO está representado por proceso BINGO con varios threads (uno por jugador).
Las bolillas que van saliendo están guardadas en un vector:
int bolillas[CANTIDAD_DE_BOLILLAS]; // del 1 al 99.
El hilo principal (main):
• Recibe por parámetro la cantidad de jugadores.
• Lanza tantos ThreadJugadores como jugadores se hayan ingresado por parámetro.
• Genera en forma aleatoria números no repetitivos del 1 al 99, cargando en el vector bolillas;
repite esta acción cada N ms (N aleatorio entre 500 y 5000ms).
• Antes de sacar una nueva bolilla, verifica la variable global g_carton_lleno (inicializada en 0);
si ésta es distinta de 0, significa que ya hay un ganador.
• Al finalizar los hilos, el main debe mostrar la cantidad de aciertos de cada jugador.
ThreadJugador (uno por jugador):
Cada ThreadJugador genera al azar 5 números del 1 al 99 (no repetidos), y los guarda en un
vector (intcarton[5]). Y realiza lo siguiente:
1. Verifica cada 500ms el vector de bolillas; si encuentra que tiene uno de los números que tiene
en su cartón, suma 1 a la variable cant_aciertos (local del thread e inicializada en 0).
Sólo los números nuevos deben llevar un control de los números que ya marcó.
2. En caso de completar el cartón, cambia el valor de la variable g_carton_lleno (utilizar mutex)
por el número de jugador.
Por cada ciclo, verifica el valor variable global g_carton_lleno (inicializada en 0); si ésta es
distinta de 0 significa que ya hay un ganador. Finaliza y devuelve la cantidad de aciertos.
Realizar los siguientes puntos:
1. El vector bolillas debe estar creado en el main y deberá ser pasado por parámetro a cada
thread (sólo el puntero).
2. Buscar la manera de que cada ThreadJugador sólo chequee el vector bolillas una vez que
salió una nueva bolilla (eliminando la consulta constante sobre el vector)
