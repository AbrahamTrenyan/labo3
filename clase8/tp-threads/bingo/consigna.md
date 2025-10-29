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
vector (int carton[5]). Y realiza lo siguiente:
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
